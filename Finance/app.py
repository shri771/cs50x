import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from helpers import apology, login_required, lookup, usd
from werkzeug.security import check_password_hash, generate_password_hash

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "POST":
        return

    else:

        user_id = session["user_id"]
        rows = db.execute(
            "SELECT stock,quantity FROM stocks WHERE user_id = ? and NOT quantity = 0 ",
            user_id,
        )

        # Fill the data array
        data = []
        total = 0
        for row in rows:
            price = lookup(row["stock"])
            entery = {
                "symbol": row["stock"],
                "shares": row["quantity"],
                "price": usd(price["price"]),
                "total": usd(price["price"] * int(row["quantity"])),
            }
            data.append(entery)

            total += price["price"] * int(row["quantity"])

        row_2 = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        cash = row_2[0]["cash"]
        value = usd(cash + total)
        cash = usd(cash)

        return render_template("index.html", data=data, cash=cash, value=value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol", "").upper()
        quantity = int(request.form.get("shares", 0))
        user_id = session["user_id"]

        # Look up price
        quote = lookup(symbol)
        if quote is None or quantity <= 0:
            return apology("Invalid symbol or quantity")

        cost = quantity * quote["price"]

        # Check user’s balance
        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        if not rows or rows[0]["cash"] < cost:
            return apology("Insufficient Balance")
        balance = rows[0]["cash"] - cost

        # Deduct cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, user_id)

        # Add to their portfolio
        exists = db.execute(
            "SELECT 1 FROM stocks WHERE user_id = ? AND stock = ?", user_id, symbol
        )
        if exists:
            db.execute(
                "UPDATE stocks SET quantity = quantity + ? WHERE user_id = ? AND stock = ?",
                quantity,
                user_id,
                symbol,
            )
        else:
            db.execute(
                "INSERT INTO stocks (user_id, stock, quantity) VALUES (?, ?, ?)",
                user_id,
                symbol,
                quantity,
            )

        # Add the transaction to transaction history
        db.execute(
            "INSERT INTO transactions  (user_id, symbol, quantity, type) VALUES (?, ?, ?, 'buy')",
            user_id,
            symbol,
            quantity,
        )

        return redirect("/")

    # GET request
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    # Get the history
    rows = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)

    # Store the history in a list of array
    data = []
    for row in rows:
        entery = {
            "symbol": row["symbol"],
            "shares": row["quantity"],
            "type": row["type"],
            "transacted": row["transacted"],
        }
        data.append(entery)

    return render_template("transaction.html", data=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":

        # lookup for the symbol
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote is not None:
            price = usd(quote["price"])
            return render_template(
                "quoted.html",
                name=quote["name"],
                price=price,
            )
        else:
            return apology("Stock Not Found", 400)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # check for a Valid username
        username = request.form.get("username")
        username_db = db.execute("SELECT username FROM users")
        password = request.form.get("password")
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure username is not used
        for user in username_db:
            if username == user["username"]:
                return apology("username exists", 400)

        # Ensure confirm password is provide
        if not request.form.get("confirmation"):

            return apology("must provide confirm password", 400)

        # Ensure confirm password and the password match
        if request.form.get("confirmation") != password:

            return apology("must provide confirm password", 400)

        # Register the User
        pass_hash = generate_password_hash(password, method='scrypt', salt_length=16)
        db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?)", username, pass_hash
        )
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol", "").upper()
        user_id = session["user_id"]

        # Check for valid quantity
        raw = request.form.get("shares")  # e.g. "42"
        try:
            quantity = int(raw)
        except (TypeError, ValueError):
            return apology("Quantity must be an integer")

        if raw is None:
            return apology("Enter quantity")
        # Look up price
        quote = lookup(symbol)
        if quote is None or quantity <= 0 or not quantity:
            return apology("Invalid symbol or quantity")

        cost = quantity * quote["price"]

        # Check user has tha stocs
        rows = db.execute(
            "SELECT * FROM stocks,users WHERE user_id = ? and stock = ? and stocks.user_id = users.id ",
            user_id,
            symbol,
        )
        if rows[0]["quantity"] < quantity:
            return apology("Insufficient Stocks")
        balance = rows[0]["cash"] + cost

        # Deduct cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, user_id)

        # Add to their portfolio
        db.execute(
            "UPDATE stocks SET quantity = quantity - ? WHERE user_id = ? AND stock = ?",
            quantity,
            user_id,
            symbol,
        )

        # Add the transaction to the transaction history
        db.execute(
            "INSERT INTO transactions  (user_id, symbol, quantity, type) VALUES (?, ?, ?, 'sell')",
            user_id,
            symbol,
            quantity,
        )

        return redirect("/")

    # GET request
    return render_template("sell.html")
