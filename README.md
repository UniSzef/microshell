### Microshell

## Autor
Bartosz Hornung

## Opis projektu
MikroShell to jeden z pierwszych projektów, który pozwalał mi się zapoznać z programowaniem w języku C w środowisku Linux. Aplikacja umożliwia obsługę podstawowych poleceń powłoki oraz własnych implementacji popularnych komend. Projekt jest wprowadzeniem do programowania systemowego, zarządzania procesami, obsługi sygnałów i pracy z plikami w systemach operacyjnych opartych na UNIX/Linux.

## Główne funkcjonalności
- Obsługa podstawowych komend systemowych – cd, echo, exit, oraz komendy wykonywane przez execvp.
- Historia poleceń – możliwość wyświetlania (history), czyszczenia (history -c) oraz zapisywania (history -w i history -a).
- Własna implementacja cat – dodatkowe opcje, takie jak numerowanie linii (cat -n) i wyświetlanie znaków białych (cat -A).
- Zarządzanie procesami – użycie fork() do tworzenia procesów podrzędnych, execvp() do uruchamiania komend oraz wait() do synchronizacji.
- Obsługa sygnałów – m.in. SIGINT dla poprawnej obsługi Ctrl + C.

## Stos technologiczny
- Język programowania: C
- Środowisko: Linux / UNIX
- Funkcje systemowe: fork(), execvp(), wait(), getpwuid(), chdir(), signal(), getenv(), setenv().

## Jak działa MikroShell
Program wyświetla prompt użytkownika, który zawiera nazwę katalogu i użytkownika.
Oczekuje na wpisanie komendy, a następnie analizuje jej argumenty.
Jeśli komenda jest zaimplementowana wewnętrznie (help, cd, history, cat), zostaje przetworzona bezpośrednio.
Jeśli jest to inna komenda systemowa, MikroShell tworzy nowy proces za pomocą fork() i wykonuje komendę przy użyciu execvp().
Program obsługuje sygnały systemowe, m.in. SIGINT, aby zapewnić prawidłowe działanie Ctrl + C w procesach potomnych.

## Podsumowanie
MikroShell to prosty, ale funkcjonalny projekt, który wprowadził mnie w świat systemów operacyjnych Linux, programowania w C i zarządzania procesami. 
"Nie musisz być wielki, żeby zacząć, ale musisz zacząć, żeby być wielki." — Zig Ziglar
