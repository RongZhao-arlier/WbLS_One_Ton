#!/bin/csh
setenv RATROOT /public/users/zhaoy/softwares/rat-pac
setenv PATH "$RATROOT/bin:$PATH"
if ({$?LD_LIBRARY_PATH}) then
  setenv LD_LIBRARY_PATH "${RATROOT}/lib:$LD_LIBRARY_PATH"
else
  setenv LD_LIBRARY_PATH "${RATROOT}/lib"
endif

# For Mac OS X
if ({$?DYLD_LIBRARY_PATH}) then
  setenv DYLD_LIBRARY_PATH "${RATROOT}/lib:$DYLD_LIBRARY_PATH"
else
  setenv DYLD_LIBRARY_PATH "${RATROOT}/lib"
endif

if ({$?PYTHONPATH}) then
  setenv PYTHONPATH "$RATROOT/python:$PYTHONPATH"
else
  setenv PYTHONPATH "$RATROOT/python"
endif
setenv GLG4DATA "$RATROOT/data"
