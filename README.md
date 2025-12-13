# 🚀 Matrix Class - Projekt (GitHub Copilot)

Projekt realizowany w ramach przedmiotu **Programowanie Zaawansowane**.
Aplikacja to autorska implementacja klasy macierzy kwadratowej (**Matrix**) w języku C++, napisana przy ścisłej współpracy z asystentem **GitHub Copilot**.

---

## 🛠 Technologie i Narzędzia

* **Język:** C++ (Modern C++, standard C++17)
* **AI Assistant:** GitHub Copilot (generowanie kodu, dokumentacji)
* **Automatyzacja:** Bash (Linux/macOS) & Batch (Windows)
* **IDE/Edytor:** VS Code

---

## 📂 Struktura Projektu

```text
.
├── data/
│   ├── input_matrix_A.txt     # 📄 Dane wejściowe dla macierzy A
│   └── input_matrix_B.txt     # 📄 Dane wejściowe dla macierzy B
├── include/
│   └── matrix.h               # 🧠 Deklaracja klasy Matrix i jej metod
├── src/
│   ├── main.cpp               # 🏁 Punkt wejścia (testy funkcjonalności)
│   ├── matrix_core.cpp        # ⚙️ Rdzeń (konstruktory, alokacja pamięci)
│   ├── matrix_operators.cpp   # ➕ Przeciążenia operatorów (+, -, *, ==, <<)
│   └── matrix_utils.cpp       # 🛠 Metody narzędziowe (losowanie, transpozycja, wzory)
│
├── doxygen.pdf                # Dokumentacja doxygen
├── dokumentacja.pdf           # Dokumentacja LaTeX
├── run.sh                     # 🐧 Skrypt uruchamiający (Linux/macOS)
├── run.bat                    # 🪟 Skrypt uruchamiający (Windows)
├── .gitignore                 # Pliki ignorowane przez Git
└── README.md                  # 📄 Dokumentacja projektu


```

## Wymagania wstępne ⚙️

Aby uruchomić projekt, upewnij się, że masz zainstalowane:
* **Kompilator C++** wspierający standard C++17 (np. g++)

## Kompilacja i Uruchomienie (Deployment)

1.  **Sklonuj repozytorium:**
    ```sh
    git clone https://github.com/dmichura/matrix-copilot.git
    ```
2. **Przejdź do katalogu projektu:**
    ```sh
    cd matrix-copilot
    ```
3.  **Skompiluj program:**
    * **Dla Linux / macOS (run.sh):**
        ```sh
        ./run.sh
        ```
    * **Dla Windows (run.bat):**
        ```bat
        run.bat
        ```
4. **Generowanie doxygen (Opcjonalnie)**
    * Wygeneruj doxygena
        ```sh
        doxygen
        ```
    * Stwórz pdf z latexa
        ```sh
        cd docs/latex && make
        ```

## 👤 Autor

* Dominik Jonik - [dominikJon](https://github.com/dominikJon)
* Sebastian Tatara - [xSebix10](https://github.com/xSebix10)
* Dawid Michura - [dmichura](https://github.com/dmichura)