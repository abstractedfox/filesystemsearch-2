import subprocess

#result = subprocess.run(["gdb", "./bin/a.out", "--ex", "run", "--batch"])
result = subprocess.run(["./bin/a.out"])

while result.returncode == 0:
    #result = subprocess.run(["gdb", "./bin/a.out", "--ex", "run", "--batch"])
    result = subprocess.run(["./bin/a.out"])
