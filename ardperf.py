from time import sleep
from pathlib import Path
from typing import Sequence
from argparse import ArgumentParser

from serial import Serial
from psutil import cpu_percent, virtual_memory, disk_usage


def format_output(data: int) -> str:
    return f"0{data}" if data < 10 else str(data)


def write_stats(device: Path, verbose: bool = False) -> None:
    with Serial(str(device)) as serial:
        while True:
            # Disk usage
            disk_usage_value = int(disk_usage("/").percent)

            # If the number of percentages consists of a single digit,
            # it is safer to add 0 at the beginning so that there are
            # no display errors.
            #
            # Then similarly.
            disk_output = format_output(disk_usage_value)

            # CPU usage
            cpu_usage_value = int(cpu_percent(interval=1))
            cpu_output = format_output(cpu_usage_value)

            # RAM usage
            ram_usage_value = int(virtual_memory().percent)
            ram_output = format_output(ram_usage_value)

            # Ouput
            output = f"DISK SIZE {disk_output}%\nCPU {cpu_output}% RAM {ram_output}%"

            if verbose:
                print(output)

            # Serial
            serial.write(output.encode())

            # Sleep
            sleep(2)


def main(args: Sequence[str] | None = None) -> None:
    parser = ArgumentParser(prog="ardperf")
    parser.add_argument("--device", type=Path, required=True)
    parser.add_argument("--verbose", action="store_true")
    args = parser.parse_args()
    write_stats(args.device, args.verbose)


if __name__ == "__main__":
    main()
