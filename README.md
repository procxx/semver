# Semver

## Описание
Простая реализация логики семантического версионирования с упором на embedded решения. В данном варианте используется шаблон  `Major.Minor.Patch-PreRelease.PreReleaseNumber`, при этом часть `-PreRelease.PreReleaseNumber` не обязательная. Часть, которая отвечает за сборочные параметры (которая начинается после `+`) в данном варианте для простоты не используется. 

Мажорная, минорная и версия патча могут быть любыми не отрицательными числами, PreRelease - `alpha`, `betha`, `rc`, номер PreRelease от нуля (не отображается) до 99 (и то, если версия дошла до `-alpha.10` - уже что-то пошло не так :) ).

Более подробно о семантическом версионировании можно почитать [здесь](http://semver.org).

## Примеры
### Создание:
```C++
utils::Semver version;
```
При этом будет задана версия `0.1.0`.
Версию можно задать параметрами конструктора:
```C++
utils::Semver version(1, 0, 0, utils::Semver::PreRelease::Alpha);
```
После преобразования в строку это даст `1.0.0-alpha`.
Так же возможно задание версии из строки:
```C++
utils::Semver version("1.12.0");
```
Или:
```C++
utils::Semver version;
version.fromString("1.12.0");
```
Или задать через метод set:
```C++
utils::Semver version;
version.set(2, 0, 0, utils::Semver::PreRelease::ReleaseCandidate); // 2.0.0-rc
```
### Вывод
Для вывода можно использовать либо метод `toString`, либо приведение:
```C++
std::printf("Version: %s\n", version.toString());
std::printf("Version: %s\n", (const char*)version);
```
Все поля версий (major, minor, etc) являются открытыми и свободны в использовании.

### Сравнение
Для сравнения версий можно использовать как операторы `>`,`<`,`==`, так и методы:
```C++
if(version1.isEquals(version2)) { /* ... */ }
if(version1.isGreaterThen(version2)) { /* ... */ }
if(version1.isLesserThen(version2)) { /* ... */ }

if(version1 == version2) { /* ... */ }
if(version1 > version2) { /* ... */ }
if(version1 < version2) { /* ... */ }
```
