#### Semântica dirigida por sintaxe

- Semantica denotacional: Gramática de regras semânticas.

**Definição**: Diz-se que uma gramática L.C. é uma máquina aumentada de regras semânticas,
ou simplesmente gramática de regras semânticas se a mesma tem suas produções acompanhadas de cálculo de atributos
associados.

Define-se atributos associados a uma gramática a coleção...

Gramatica       | Gramatica Sintatica
----------------|-----------------------------------
E -> E + T OR T | E.t <- E.t T.t +.t OR E.t <- T.t
T -> T x F OR F | T.t <- T.t F.t x.t OR T.t <- F.t
F -> n OR (E)   | F.t <- n.t OR F.t <- E.t
