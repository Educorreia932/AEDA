1. B
2. E
3. A
4. C
5. C
6. A 
7. C
8. Uma classe abstrata é uma classe que possui declaração para um membro-função, mas não a sua definição, tratando assim de uma *função virtual* (em C++, isto é feito colocando `= 0` após a declaração da função). Assim, não é possível instanciar um objeto de uma classe abstrata, mas sim apenas, objetos das classes derivadas da classe base, sendo que estes teriam de implementar os membros-funções não declarados da classe abstrata.
A utilidade de uma classe abstrata reside no facto de «obrigar» a utilizar apenas as subclasses de uma superclasse, sem nunca instanciar um objeto desta última.
9. Duas das vantagens de tal são poder efetuar alterações diretamente a essa classe X (não sendo assim necessário returnar a classe depois de a alterarmos) e a poupança de memória provinda do facto de não realizarmos uma cópia da classe X de cada vez que invocámos essa função, uma vez que acedemos ao espaço de memória já reservado para o objeto da classe X existente.
10. Quando o primeiro *pivot* escolhido é o menor elemento do vetor isso acontece, uma vez que nenhum outro elemento será menor do que este. Assim o vetor original fica divido entre dois outros, de tamanho *n - 1* e *1* (sendo este último constituído unicamente pelo pivot e outro por todos os elementos, exceto o pivot), em vez de dois, ambos de tamanho *n / 2* (aproxidamente, no caso médio)