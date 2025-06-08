# PP8

## Goal

In this exercise you will:

* Parse **command-line flags** and **parameters** in C using `getopt` and `atoi`.
* Prompt for **interactive** input using `scanf` and demonstrate file scanning with `fscanf`.
* Read input from **standard input** via shell redirection.
* Implement and modularize a **symmetric Caesar cipher** and extend it to a **prototype asymmetric** XOR cipher, compiling and linking multiple source files.

**Important:** Start a stopwatch when you begin and work uninterruptedly for **90 minutes**. When time is up, stop immediately and record exactly where you paused.

---

## Workflow

1. **Fork** this repository on GitHub.
2. **Clone** your fork locally.
3. Create a `solutions/` directory at the project root:

   ```bash
   mkdir solutions
   ```
4. Add each task’s source file under `solutions/` (e.g., `solutions/getopt_flags.c`).
5. **Commit** and **push** your changes to GitHub.
6. **Submit** your GitHub repository link for review.

---

## Prerequisites

* GNU C compiler (`gcc`).
* Familiarity with:

  * `getopt` (include `<unistd.h>`)
  * `atoi` (include `<stdlib.h>`)
  * Standard I/O: `printf`, `scanf`, `fscanf`, `fgets`
  * Shell I/O redirection
  * Manual compilation and linking
* Consult man-pages:

  ```bash
  man getopt   # option parsing
  man atoi     # string to integer conversion
  man scanf    # interactive input
  man fscanf   # file scanning
  ```

---

## Tasks

### Task 1: Command-line Flags Only

**Objective:** Parse simple flags without arguments.

1. Create `solutions/getopt_flags.c`:

   ```c
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>

   int main(int argc, char *argv[]) {
       int opt;
       int flag_a = 0, flag_b = 0;

       while ((opt = getopt(argc, argv, "ab")) != -1) {
           if      (opt == 'a') flag_a = 1;
           else if (opt == 'b') flag_b = 1;
           else {
               fprintf(stderr, "Usage: %s [-a] [-b]\n", argv[0]);
               exit(EXIT_FAILURE);
           }
       }

       printf("flag_a=%d, flag_b=%d\n", flag_a, flag_b);
       return 0;
   }
   ```
2. Compile and test:

   ```bash
   gcc -o solutions/getopt_flags solutions/getopt_flags.c
   ./solutions/getopt_flags -a -b
   ```

---

### Task 2: Command-line Parameters & File Names

**Objective:** Parse options with arguments, including input and output file names.

1. Create `solutions/getopt_params.c`:

   ```c
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>

   int main(int argc, char *argv[]) {
       int opt;
       int number = 0;
       char *str = NULL;
       char *infile = NULL, *outfile = NULL;

       while ((opt = getopt(argc, argv, "n:s:i:o:")) != -1) {
           if      (opt == 'n') number  = atoi(optarg);
           else if (opt == 's') str     = optarg;
           else if (opt == 'i') infile  = optarg;
           else if (opt == 'o') outfile = optarg;
           else {
               fprintf(stderr, "Usage: %s -n num -s str -i infile -o outfile\n", argv[0]);
               exit(EXIT_FAILURE);
           }
       }

       printf("number=%d, string=%s, infile=%s, outfile=%s\n",
              number,
              str     ? str     : "(null)",
              infile  ? infile  : "(none)",
              outfile ? outfile : "(none)");
       return 0;
   }
   ```
2. Compile and test:

   ```bash
   gcc -o solutions/getopt_params solutions/getopt_params.c
   ./solutions/getopt_params -n 42 -s hello -i input.txt -o output.txt
   ```

#### Reflection Questions

1. **How do you pass a file name to a program using the `-i` and `-o` options?**

**Antwort zu 1:**
Dateinamen werden über die Kommandozeile als Argumente zu den Optionen `-i` (für Eingabedatei) und `-o` (für Ausgabedatei)
übergeben. Der Dateiname folgt direkt auf die jeweilige Option, z. B.:

`./getopt_params -i input.txt -o output.txt`

Im Code werden diese Argumente mit `optarg` ausgelesen und in Variablen gespeichert.
   
2. **What are typical use cases for parameters versus flags? How do the differ from one another?**

**Antwort zu 2:**
Flags sind einfach Schalter, die ein bestimmtes Verhalten aktivieren oder deaktivieren, z. B. `-v` für ausführliche Ausgabe.
Sie benötigen kein Argument. Parameter hingegen übergeben konkrete Werte oder Informationen an das Programm, z. B. Zahlen, Strings
oder Dateinamen. Sie benötigen ein Argument. Während Flags binäre Zustände darstellen, liefern Parameter inhaltliche Eingaben für die
Programmlogik.

---

### Task 3: Interactive Input with `scanf` & `fscanf`

**Objective:** Prompt for user input at runtime and read structured data from a file.

1. Create `solutions/interactive.c`:

   ```c
   #include <stdio.h>
   #define BUF_SIZE 100

   int main(void) {
       char name[BUF_SIZE];
       int age;

       printf("Enter your name: ");
       scanf("%99s", name);
       printf("Hello, %s!\n", name);

       printf("Enter your age: ");
       scanf("%d", &age);
       printf("You are %d years old.\n", age);

       // File scanning
       FILE *fp = fopen("data.txt", "r");
       if (!fp) { perror("fopen"); return 1; }
       char fname[BUF_SIZE];
       int fage;
       if (fscanf(fp, "%99s %d", fname, &fage) == 2) {
           printf("File data: %s is %d years old.\n", fname, fage);
       }
       fclose(fp);
       return 0;
   }
   ```
2. Provide `solutions/data.txt` containing:

   ```text
   Alice 30
   ```
3. Compile and run:

   ```bash
   gcc -o solutions/interactive solutions/interactive.c
   ./solutions/interactive
   ```

#### Reflection Question

* **Why is a run-to-completion (batch) approach often preferable to interactive input?**
**Antwort:**

  Ein Run-to-Completion (Batch)-Ansatz verarbeitet alle Eingaben automatisch und durchläuft das Programm vollständig
  ohne Benutzerinteraktion. Das hat mehrere Vorteile:

  - Automatisierbarkeit: Batch-Programme lassen sich leicht in Skripte oder automatisierte Abläufe einbinden, wodurch sich Prozesse
    wiederholbar und ohne manuellen Aufwand ausführen lassen.
  - Effizienz: Ohne Wartezeiten für Benutzereingaben läuft das Programm meist schneller und durchgängig ab.
  - Reproduzierbarkeit: Ergebnisse sind konsistent, da Eingaben vordefiniert und festgelegt sind, was Tests und Debugging erleichtert.
  - Skalierbarkeit: Batch-Programme können große Datenmengen oder viele Dateien hintereinander verarbeiten, ohne dass ein Nutzer ständig eingreifen muss.

  Im Gegensatz dazu ist die interaktive Eingabe zwar benutzerfreundlich für kleine Tests oder Einzelanwendungen, aber für automatisierte oder groß
  angelegte Abläufe oft unpraktisch und fehleranfällig.

---

### Task 4: Input Redirection from STDIN

**Objective:** Read input supplied via shell redirection.

1. Create `solutions/redirect_input.c`:

   ```c
   #include <stdio.h>
   #define BUF_SIZE 256

   int main(void) {
       char buf[BUF_SIZE];
       if (fgets(buf, BUF_SIZE, stdin))
           printf("You entered: %s", buf);
       return 0;
   }
   ```
2. Create `solutions/input.txt` with sample text.
3. Compile and run:

   ```bash
   gcc -o solutions/redirect_input solutions/redirect_input.c
   ./solutions/redirect_input < solutions/input.txt
   ```

#### Reflection Question

* **What is the difference between redirecting to stdin and explicitly opening a file with `fopen`?**
  **Antwort:**
  Der Unterschied liegt vor allem in der Art, wie und wo die Datei geöffnet wird:

  **Umleitung auf `stdin`**
  - Erfolgt außerhalb des Programms durch die Shell (<datei.txt)
  - Das Programm liest einfach wie gewohnt von `stdin` beokmmt aber die Dateiinhalte statt Tastatureingaben
  - Vorteil: Kein Dateipfad oder `fopen` im Code nötig - das Programm bleibt einfach und flexibel

  **Datei mit`fopen` öffnen:**
  - Datei wird innerhalb des Programms explizit geöffnet.
  - Der Pfad zur Datei muss bekannt und fest im Code oder als Argument angegeben sein.
  - Vorteil: Mehr Kontrolle, z. B. beim Öffnen mehrerer Dateien oder beim gezielten Umgang mit Fehlern.

---

### Task 5: Caesar Cipher & Prototype Asymmetric XOR Cipher

**Objective:** Implement and modularize two cipher algorithms.

#### 5.1 Symmetric Caesar Cipher

1. **Header (`cipher.h`)**:

   ```c
   #ifndef CIPHER_H
   #define CIPHER_H
   char encrypt_char(char c, int shift);
   char decrypt_char(char c, int shift);
   #endif
   ```
2. **Implementation (`cipher.c`)**:

   ```c
   #include "cipher.h"

   char encrypt_char(char c, int shift) {
       if (c >= 'A' && c <= 'Z') return 'A' + (c - 'A' + shift) % 26;
       if (c >= 'a' && c <= 'z') return 'a' + (c - 'a' + shift) % 26;
       return c;
   }

   char decrypt_char(char c, int shift) {
       return encrypt_char(c, 26 - (shift % 26));
   }
   ```
3. **Driver (`caesar.c`)**:

   ```c
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>
   #include "cipher.h"

   void usage(const char *prog) {
       fprintf(stderr, "Usage: %s -e shift|-d shift -i infile -o outfile\n", prog);
       exit(EXIT_FAILURE);
   }

   int main(int argc, char *argv[]) {
       int opt, shift = 0, enc = -1;
       char *infile = NULL, *outfile = NULL;

       while ((opt = getopt(argc, argv, "e:d:i:o:")) != -1) {
           if      (opt == 'e') { shift = atoi(optarg); enc = 1; }
           else if (opt == 'd') { shift = atoi(optarg); enc = 0; }
           else if (opt == 'i') infile = optarg;
           else if (opt == 'o') outfile = optarg;
           else usage(argv[0]);
       }

       if (enc < 0 || !infile || !outfile) usage(argv[0]);

       FILE *fin = fopen(infile, "r");
       if (!fin) { perror("fopen infile"); exit(EXIT_FAILURE); }
       FILE *fout = fopen(outfile, "w");
       if (!fout) { perror("fopen outfile"); exit(EXIT_FAILURE); }

       int c;
       while ((c = fgetc(fin)) != EOF) {
           char out;
           if (enc)
               out = encrypt_char(c, shift);
           else
               out = decrypt_char(c, shift);
           fputc(out, fout);
       }

       fclose(fin);
       fclose(fout);
       return 0;
   }
   ```
4. **Compile & link**:

   ```bash
   gcc -c solutions/cipher.c -o solutions/cipher.o
   gcc -c solutions/caesar.c -o solutions/caesar.o
   gcc solutions/caesar.o solutions/cipher.o -o solutions/caesar
   ```
5. **Test**:

   ```bash
   ./solutions/caesar -e 3 -i input.txt -o enc.txt
   ./solutions/caesar -d 3 -i enc.txt -o dec.txt
   ```

#### 5.2 Prototype Asymmetric XOR Cipher

1. **Header (`asym.h`)**:

   ```c
   #ifndef ASYM_H
   #define ASYM_H
   char encrypt_xor(char c, char key);
   char decrypt_xor(char c, char key);
   #endif
   ```
2. **Implementation (`asym.c`)**:

   ```c
   #include "asym.h"

   char encrypt_xor(char c, char key) { return c ^ key; }
   char decrypt_xor(char c, char key) { return c ^ key; }
   ```
3. **Driver (`advanced_cipher.c`)**:

   ```c
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <unistd.h>
   #include "cipher.h"
   #include "asym.h"

   void usage(const char *prog) {
       fprintf(stderr, "Usage: %s -m <caesar|xor> -e key|-d key -i infile -o outfile\n", prog);
       exit(EXIT_FAILURE);
   }

   int main(int argc, char *argv[]) {
       int opt, enc = -1, key = 0;
       char *mode = NULL, *infile = NULL, *outfile = NULL;

       while ((opt = getopt(argc, argv, "m:e:d:i:o:")) != -1) {
           if      (opt == 'm') mode = optarg;
           else if (opt == 'e') { key = atoi(optarg); enc = 1; }
           else if (opt == 'd') { key = atoi(optarg); enc = 0; }
           else if (opt == 'i') infile = optarg;
           else if (opt == 'o') outfile = optarg;
           else usage(argv[0]);
       }

       if (!mode || enc < 0 || !infile || !outfile) usage(argv[0]);

       FILE *fin = fopen(infile, "r");
       if (!fin) { perror("fopen infile"); exit(EXIT_FAILURE); }
       FILE *fout = fopen(outfile, "w");
       if (!fout) { perror("fopen outfile"); exit(EXIT_FAILURE); }

       int c;
       while ((c = fgetc(fin)) != EOF) {
           char out;
           if (strcmp(mode, "caesar") == 0) {
               if (enc)
                   out = encrypt_char(c, key);
               else
                   out = decrypt_char(c, key);
           } else if (strcmp(mode, "xor") == 0) {
               if (enc)
                   out = encrypt_xor(c, (char)key);
               else
                   out = decrypt_xor(c, (char)key);
           } else {
               usage(argv[0]);
           }
           fputc(out, fout);
       }

       fclose(fin);
       fclose(fout);
       return 0;
   }
   ```
4. **Compile & link**:

   ```bash
   gcc -c solutions/cipher.c solutions/asym.c solutions/advanced_cipher.c
   gcc solutions/cipher.o solutions/asym.o solutions/advanced_cipher.o -o solutions/advanced_cipher
   ```
5. **Test both modes**:

   ```bash
   ./solutions/advanced_cipher -m caesar -e 3 -i input.txt -o enc.txt
   ./solutions/advanced_cipher -m caesar -d 3 -i enc.txt -o dec.txt
   ./solutions/advanced_cipher -m xor    -e 42 -i input.txt -o xor_enc.txt
   ./solutions/advanced_cipher -m xor    -d 42 -i xor_enc.txt -o xor_dec.txt
   ```

#### Reflection Question

* **Explain in your own words what the encryption and decryption processes are doing in both ciphers.**

  **Antwort:**
  
  **Caesar-Cipher (symmetrisch)**
  Die Caesar-Verschlüsselung verschiebt jeden Buchstaben im Alphabet um eine feste Anzahl an Positionen.
  Im vorliegenden Beispiel um 3 Positionen nach rechts, aus `D` wird bei einem Shift von 3 --> `G`.

  - Verschlüsselung: Zeichenweise Addition eines festen Schlüssels (Shift) zum Buchstaben.
  - Entschlüsselung: Subtraktion desselben Schlüssels (oder alternativ: Addition von `26 - shift`), um den Originalbuchstaben wiederherzustellen.

  Nur Buchstaben werden verändert. Andere Zeichen wie z. B. Leerzeichen oder Satzzeichen bleiben unverändert.

  **XOR-Verschlüsselung**
  Die XOR-Verschlüsselung vergleicht jedes Zeichen bitweise mit einem Schlüssel. Dabei wird für jedes Bit entschieden:

  - Wenn beide Bits gleich sind (0 und 0 oder 1 und 1) --> Ergebnis ist 0.
  - Wenn beide Bits unteschiedliche sind ( 0 und 1 oder 1 und 0) --> Ergebnis ist 1.

  Wenn derselbe XOR-Vergleich noch einmal auf die verschlüsselte Nachricht mit dem gleichen Schlüssel angewendet wird, erhält
  man den ursprünglichen Text zurück.

  Beispiel:

  Buchstabe A --> hat den ASCII-Code 65, also binär: 01000001
  Schlüssel K --> hat den ASCII-Code 75, also binär: 01001011

  Vergleich:

  01000001 (A) Buchstabe
  01001011 (K) Schlüssel
  =
  00001010 (=verschlüsselter Buchstabe)

  Rückwärtsvergleich:

  00001010 (verschlüsselter Buchstabe)
  01001011 (Schlüssel)
  =
  01000001 (Buchstabe A)
  
  



---

**Remember:** Stop after **90 minutes** and record where you stopped.
