@echo off

set /p Build=<./utils/build-version/ver64.txt
set /a Build=%Build%+1
>./utils/build-version/ver64.txt echo %Build%
>./utils/build-version/ver64.h echo #define AUTO_VERSION %Build%
>>./utils/build-version/ver64.h echo #define AUTO_VERSION_STR ^"%Build%^"

set /a RelWhole = %Build% / 100
set /a RelFraction = %Build% %% 100
set RelVer=%RelWhole%.%RelFraction%
>>./utils/build-version/ver64.h echo #define AUTO_VERSION_RELEASE %RelVer%
>>./utils/build-version/ver64.h echo #define AUTO_VERSION_RELEASE_STR ^"%RelVer%^"
