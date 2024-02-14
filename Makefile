VSVARSPATH = "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
SOURCE = main.c
OUT = out

build: $(SOURCE)
	@if not exist "$(OUT)" mkdir $(OUT)
	@if not exist "$(OUT)\obj" mkdir $(OUT)\obj
	@call $(VSVARSPATH) x64 \
		& cl /Fo$(OUT)\obj\ $(SOURCE) /link /out:$(OUT)\adsfh.exe

clean:
	@rmdir out /s /q

.PHONY: build clean