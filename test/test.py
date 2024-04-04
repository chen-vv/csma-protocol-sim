import os
import subprocess

import pytest


def test_csma():
    os.chdir("..")
    subprocess.run(["make"])
    subprocess.run(["./csma", "input.txt"])

    with open("output.txt") as f:
        output = f.read().strip()

    assert float(output) == 0.42


def main():
    pytest.main(["-v"])
