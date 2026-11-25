# Common

## Running the tests

The test runner requires `g++` with C++17 support available on `PATH`.
Run it from the `test` directory because the batch file uses paths relative
to that directory.

From PowerShell at the repository root:

```powershell
Set-Location .\test
.\run_test.bat
```

Or from Command Prompt at the repository root:

```bat
cd test
run_test.bat
```

The script builds and runs the CMN, conversions, Earth, atmosphere, and
transform test programs. It stops and returns a failure code if a build or
test fails. Generated executables are written into `test`.

## TODO
- [ ] Add Filter test cases.
- [ ] Add temperature conversions to conversions code and replace one-offs in atmo code.
- [ ] Add ficticious force calcs in earth code.
