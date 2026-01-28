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

### Kompilacja testow:
Niestety nie miałem wystarczająco dużo czasu żeby napisac wszystkie testy. Zrobilem minimalny zarys testow, który można skompilować za pomocą komend:
Build tests
```
cd app/src/test/cpp
cmake -S . -B build
cmake --build build
./build/Debug/native_tests
```
