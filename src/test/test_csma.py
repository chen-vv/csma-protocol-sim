import os
import queue
import subprocess
import threading
import time

import pytest


@pytest.mark.parametrize(
    "input_filename, expected_output_data",
    [("test_input.txt", 0.73)],
)
def test_csma(input_filename, expected_output_data):
    with open(input_filename, "r") as input_file:
        input_data = input_file.read()

    simulation_process = subprocess.Popen(["../../csma", input_filename])

    simulation_process.wait()

    with open("output.txt", "r") as output_file:
        output_data = output_file.read()

    assert output_data == expected_output_data


if __name__ == "__main__":
    pytest.main(["-v"])
