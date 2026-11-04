<p align="center">
  <img src="assets/banner-pixel.png" alt="Banner em pixel art vermelho, vinho e preto com tema de programação" width="850" />
</p>

# Cadastro de Restaurantes em C

![C](https://img.shields.io/badge/C-A61C30?style=flat-square&logoColor=white)
![Listas](https://img.shields.io/badge/lista_encadeada-240b19?style=flat-square&logoColor=white)
![Arquivos](https://img.shields.io/badge/arquivos-89172c?style=flat-square&logoColor=white)

Projeto de estudo em C utilizando **lista encadeada** e **persistência em arquivo**.

## `01 / funcionalidades`

- Inserção e listagem de restaurantes.
- Filtros por nota mínima e tipo de comida.
- Gravação e leitura do arquivo `restaurantes.txt`.
- Liberação de memória da lista.

## `02 / execução`

```bash
gcc -std=c11 -Wall -Wextra src/main.c -o cadastro-restaurantes
./cadastro-restaurantes
```

No Windows, execute o `.exe` gerado.

## `03 / melhorias futuras`

- Substituir `system("notepad restaurantes.txt")`, dependente do Windows.
- Melhorar a validação de entradas e o tratamento de erros de arquivo.
- Testar arquivos ausentes, vazios ou malformados.

> Exercício de aprendizagem, não um sistema de produção.
