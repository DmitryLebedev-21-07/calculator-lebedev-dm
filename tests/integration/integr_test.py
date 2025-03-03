import subprocess
import pytest

def test_sum_int():
    res = subprocess.run(["./build/app.exe"], input="2+2\n", text=True, capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout) == 4

def test_mult_int():
    res = subprocess.run(["./build/app.exe"], input="12*5\n", text=True, capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout.strip()) == 60

def test_many_expressions_int():
    res = subprocess.run(["./build/app.exe"], input="2+2*2+(6/2)\n", text=True, capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout.strip()) == 9

def test_many_expressions_float():
    res = subprocess.run(["./build/app.exe", "--float"], input="4*5/(8+13)\n", text=True, capture_output=True)
    assert res.returncode == 0
    assert round(float(res.stdout.strip()), 6) == 0.952381

def test_wrong_symbol():
    res = subprocess.run(["./build/app.exe"], input="4*x\n", text=True, capture_output=True)
    assert res.returncode != 0

def test_lot_braces():
    res = subprocess.run(["./build/app.exe"], input="(((2+3)\n", text=True, capture_output=True)
    assert res.returncode != 0

def test_division_by_zero():
    res = subprocess.run(["./build/app.exe"], input="10/0\n", text=True, capture_output=True)
    assert res.returncode != 0

def test_lot_symbols_in_expression():
    res = subprocess.run(["./build/app.exe"], input="3++++3\n", text=True, capture_output=True)
    assert res.returncode != 0

def test_max_number():
    res = subprocess.run(["./build/app.exe"], input="2000000001+1\n", text=True, capture_output=True)
    assert res.returncode != 0

def test_un_minus():
    res = subprocess.run(["./build/app.exe"], input="-2+1\n", text=True, capture_output=True)
    assert res.returncode != 0
