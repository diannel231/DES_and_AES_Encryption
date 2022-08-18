# DES-and-AES
## Group members:

  Ryan Chen ryan.chen@csu.fullerton.edu

  Dianne Lopez diannel@csu.fullerton.edu

## Programming language:

  c++

## How to execute:

  To compile, simply, type ''make'' at the terminal (without the quotes).

  Type the command in the following format:

    ./cipher \<CIPHER\> \<KEY\> \<ENCDEC\> \<IN FILE\> \<OUT FILE\>

  The accepted inputs for <CIPHER> are:

    AES

    DES

  The accepted inputs for <ENCDEC> are:

    ENC

    DEC

  An example command to encrypt would be:

    ./cipher AES 0123456789abcdef ENC in.txt out1.txt

  An example command to decrypt would be:

    ./cipher DES 0123456789abcdef DEC out1.txt out2.txt

### The extra credit was not implemented.

### There are no additional notes.
