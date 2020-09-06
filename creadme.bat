echo off

echo # GCODE
echo Some code snippets that can be reused
echo.

for /D %%s in (*) do ( 
echo ## %%s
echo.

for /D %%d in (%%s/*) do ( 
echo - **%%d**
echo.

for /D %%k in (%%s/%%d/*) do ( 
echo    - **%%k**
echo.
)

)

)
pause