# Testes de Fuzzing com AFL++

## 📌 **Descrição do Projeto**

Este projeto realiza testes de fuzzing utilizando o **AFL++ (American Fuzzy Lop Plus Plus)** para identificar vulnerabilidades de memória em um programa C propositalmente inseguro.
O objetivo principal é detectar automaticamente um **buffer overflow** presente no código fornecido pela professora e analisar o crash gerado pelo fuzzer.

---

## 📄 **Programa Testado**

O programa vulnerável realiza a leitura de um arquivo de entrada e copia o conteúdo para um buffer de apenas 16 bytes usando `strcpy()`, sem qualquer verificação de tamanho:

```c
char buffer[16];
strcpy(buffer, input);  // Vulnerabilidade: buffer overflow
```

Entradas maiores que 16 bytes causam sobrescrita de memória e abortam a execução.

---

## 🚀 **Como Reproduzir o Experimento**

### **1. Instale o AFL++**

```bash
sudo apt update && sudo apt install afl++ -y
```

### **2. Compile o programa com instrumentação**

```bash
afl-gcc -o program program.c
```

### **3. Crie o diretório com as seeds**

As quatro seeds utilizadas foram:

```
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
""
{}{}{}{}
testando
```

Comandos para criação:

```bash
mkdir inputs
echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" > inputs/seed1.txt
echo "\"\"" > inputs/seed2.txt
echo "{}{}{}{}" > inputs/seed3.txt
echo "testando" > inputs/seed4.txt
```

### **4. Execute o fuzzer**

```bash
AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 \
afl-fuzz -i inputs -o outputs -- ./program @@
```

### **5. Após a execução, verifique os crashes**

```bash
ls outputs/default/crashes
```

### **6. Visualize o conteúdo do crash**

```bash
cat outputs/default/crashes/id:000000*
```

Saída esperada:

```
AAAAAAAAAAAAAAAAAAAAAA
```

### **7. Reproduza o crash manualmente**

```bash
./program outputs/default/crashes/id:000000*
```

Resultado:

```
*** buffer overflow detected ***: terminated
Aborted (core dumped)
```

---

## 🧩 **Seeds Utilizadas**

| Seed  | Conteúdo                                                                        |
| ----- | ------------------------------------------------------------------------------- |
| seed1 | `AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA` |
| seed2 | `""`                                                                            |
| seed3 | `{}{}{}{} `                                                                     |
| seed4 | `testando`                                                                      |

Essas seeds foram mutadas pelo AFL++ para gerar o arquivo que causou o crash.

---

## 💥 **Crash Identificado**

Arquivo salvo em:

```
outputs/default/crashes/id:000000,sig:06,src:000003,time:849,execs:48,op:havoc,rep:2
```

Conteúdo:

```
AAAAAAAAAAAAAAAAAAAAAA
```

O crash ocorreu por:

* exceder os 16 bytes do buffer interno
* sobrescrever a pilha
* ativar o Stack Smashing Protector
* gerar SIGABRT (sinal 6)

---

## 📚 **Conclusão**

O AFL++ demonstrou ser eficiente em:

* detectar a vulnerabilidade com rapidez,
* gerar entradas mutadas que excedem o buffer,
* revelar o *buffer overflow* de forma determinística,
* registrar automaticamente o caso mínimo que reproduz o crash.

Esse experimento demonstra a importância de:

* evitar funções inseguras como `strcpy()`;
* validar o tamanho da entrada antes de copiá-la;
* usar fuzzers para detectar vulnerabilidades ocultas.

---

## 📎 **Arquivos incluídos no projeto**

```
program.c
inputs/
outputs/
Relatorio_Fuzzing_AFL_Com_Seeds.docx
README.md
```
