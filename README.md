# Custom Seek Bar

## Kompilacja:

### Kompilacja aplikacji
**Aby skompilować projekt, należy umieścić statycznie skompilowane biblioteki skia w odpowiednich katalogach a następnie otworzyć go w Android studio i uruchomić aplikację.**

W moim przypadku skompilowane satycznie biblioteki skia umieszczone były w katalogach: 
`CustomSeekBar\app\src\main\cpp\third_parties\skia\lib\arm64-v8a\libskia.a`
`CustomSeekBar\app\src\main\cpp\third_parties\skia\lib\x86_64\libskia.a`

Niestety nie mogę ich załączyć ze względu na rozmiar.

Projekt i bibliotekę skia kompilowałem na windows 11.
Ostatni commit w repozytorium Skia:

`fd4d872b0b (HEAD -> main, origin/main, origin/HEAD) Roll vulkan-deps from c159d041dce0 to 5e75ee90603d (3 revisions)`

Skompilowane biblioteki skia dostępne są na moim prywatnym dysku google-a:
https://drive.google.com/drive/folders/1F_hUjUi3jfMpcD3aSvkZcDtBkYxvV6CP?usp=sharing

#### Błąd linkowania
W przypadku błędu budowania spowodowanego brakiem jednego z plików źródłowych w linkerze można spróbować zastosować poniższego diff-a:
```
PS C:\Users\Kawa\Desktop\CustomSeekBar> git diff app/src/main/cpp/CMakeLists.txt
diff --git a/app/src/main/cpp/CMakeLists.txt b/app/src/main/cpp/CMakeLists.txt
index b8f879f..2750943 100644
--- a/app/src/main/cpp/CMakeLists.txt
+++ b/app/src/main/cpp/CMakeLists.txt
@@ -22,7 +22,17 @@ set(CPP_SRC ${CPP_ROOT}/src)

 # ---- Find all source files ----
 file(GLOB_RECURSE CPP_SOURCES
-        ${CPP_SRC}/*.cpp
+        ${CPP_SRC}/native-lib.cpp
+        ${CPP_SRC}/App/Context.cpp
+        ${CPP_SRC}/Core/MetronomeService.cpp
+        ${CPP_SRC}/Core/SeekBarManager.cpp
+        ${CPP_SRC}/Core/SeekProxy.cpp
+        ${CPP_SRC}/Core/SeekStateListener.cpp
+        ${CPP_SRC}/Drawing/SkiaDrawer.cpp
+        ${CPP_SRC}/Utils/JNIUtils.cpp
+        ${CPP_SRC}/View/SeekBarView.cpp
+        ${CPP_SRC}/View/SeekBarViewBuilder.cpp
+        ${CPP_SRC}/View/SeekLoadingView.cpp
 )

 # ---- Skia paths ----
```

### Kompilacja testow:
Niestety nie miałem wystarczająco dużo czasu żeby napisac wszystkie testy. Zrobilem minimalny zarys testow, który można skompilować za pomocą komend:
Build tests
```
cd app/src/test/cpp
cmake -S . -B build
cmake --build build
./build/Debug/native_tests
```
