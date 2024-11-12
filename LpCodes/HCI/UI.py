import tkinter as tk
from tkinter import messagebox, ttk

def sign():
    messagebox.showinfo("Sign Up", "Signed up successfully!")
    tab_controls.select(login_tab)

def login():
    username = usr_entry.get()
    password = pass_entry.get()
    if username == "Lakshya" and password == "123":
        messagebox.showinfo("Login", "Welcome! Logged in successfully.")
        enable()
        tab_controls.forget(login_tab)
        tab_controls.forget(sign_up)
    else:
        messagebox.showerror("Login Error", "Invalid username or password")

def enable():
    tab_controls.tab(2, state="normal")
    tab_controls.tab(3, state="normal")

root = tk.Tk()
root.geometry("800x600")
root.title("PICT Hostel Management System")
root.configure(bg="lightgray")

tab_controls = ttk.Notebook(root)

# Sign Up Tab
sign_up = ttk.Frame(tab_controls)
fields = ["Name", "Branch", "Year", "Username", "Password"]
for field in fields:
    tk.Label(sign_up, text=field, font="Arial", anchor="w").pack(pady=5, fill="x")
    entry = tk.Entry(sign_up, width=40)
    if field == "Password":
        entry.config(show="*")
    entry.pack(pady=5)

sign_up_btn = tk.Button(sign_up, text="Sign Up", bg="red", fg="yellow", font="Arial", command=sign)
sign_up_btn.pack(pady=10)

# Login Tab
login_tab = ttk.Frame(tab_controls)
tk.Label(login_tab, text="Enter Username", font="Arial").pack(pady=10)
usr_entry = tk.Entry(login_tab, width=20, font="Arial")
usr_entry.pack(pady=10)

tk.Label(login_tab, text="Enter Password", font="Arial").pack(pady=10)
pass_entry = tk.Entry(login_tab, width=20, font="Arial", show="*")
pass_entry.pack(pady=10)

login_btn = tk.Button(login_tab, text="Login", bg="Red", fg="Yellow", command=login, font="Arial")
login_btn.pack(pady=20)

# Home Page Tab
home_tab = ttk.Frame(tab_controls)
tk.Label(home_tab, text="PICT Hostel Management System", bg="blue", fg="white", font=("Arial", 16, "bold")).pack(pady=20)

# Features List
features_frame = tk.Frame(home_tab, bg="lightblue", bd=2, relief="solid")
features_frame.pack(pady=10, padx=10, fill="x", expand=True)
features = [
    "1. 24/7 Security",
    "2. Unlimited Wi-Fi",
    "3. Lunch and Dinner with breakfast",
    "4. High-class amenities",
    "5. Hot Water",
    "6. Medical checkup once a week",
    "7. Daily Attendance",
    "8. Admission on the basis of CGPA"
]
for feature in features:
    tk.Label(features_frame, text=feature, bg="lightblue", font=("Arial", 12)).pack(anchor="w", padx=10, pady=2)

# Guidelines Tab
guidelines = ttk.Frame(tab_controls)
tk.Label(guidelines, text="Guidelines", bg="blue", fg="white", font=("Arial", 16, "bold")).pack(pady=20)

# Guidelines Text
guidelines_frame = tk.Frame(guidelines, bg="lightblue", bd=2, relief="solid")
guidelines_frame.pack(pady=10, padx=10, fill="x", expand=True)
guidelines_text = [
    "1. Students must adhere to hostel timings strictly.",
    "2. Visitors are allowed only during specified hours.",
    "3. No loud music or noise after 10 PM.",
    "4. Maintain cleanliness in rooms and common areas.",
    "5. Any damage to hostel property must be reported immediately.",
    "6. Ragging in any form is strictly prohibited."
]
for rule in guidelines_text:
    tk.Label(guidelines_frame, text=rule, bg="lightblue", font=("Arial", 12)).pack(anchor="w", padx=10, pady=2)

# Adding Tabs to Tab Control
tab_controls.add(sign_up, text="Sign Up")
tab_controls.add(login_tab, text="Login")
tab_controls.add(home_tab, text="Home Page", state="disabled")
tab_controls.add(guidelines, text="Guidelines", state="disabled")

tab_controls.pack(expand=1, fill="both")

root.mainloop()