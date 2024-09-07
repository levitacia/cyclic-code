# cyclic-code
Использование циклических кодов для обнаружения ошибок в сетях передачи данных / Using cyclic codes for error detection in data networks

**RU**

Рассматриваются только двоичные коды, используются многочлены с коэффициентами из GF(2)

Условные обозначения
- g(x) - порождающий многочлен
-  r = deg(g(x)) - степень порождающего многочлена, которая определяет кол-во бит контрольной суммы в кодовом слове.
- k - число информационных символов передаваемого сообщения $\overline{m}$

Передаваемое сообщение - вектор длины k
Для каждого сообщения ($\overline{m}$) кодер выполняет:
1. Формирует m(x) на основе $\overline{m}$, $deg(m(x)) \underline{<} k-1$
2. Вычисляет $c(x) = m(x) * x^r \mod{g(x)}$, $deg(c(x)) \underline{<} r-1$
3. Вычисляет многочлен $a(x) = m(x) * x^r + c(x)$
4. На основе многочлена a(x) формирует вектор $\overline{a}$ , длина которого n бит, где n = k + r.

Пример работы кодера:
0. $g(x) = x^3 + x + 1 , deg(g(x)) = 3$
1. $\overline{m}=1010, k=4$; $m(x)=1x^3 +0x^2 + 1x +0x^0$
2. $c(x)=(x^3+x)x^3 \mod{(x^3 + x + 1)} = x+1$
3. $a(x)=(x^3+x)x^3 + x + 1=x^6+x^4+x+1$
4. $\overline{a}=1010011, n=4+3=7$

Отметим, что a(x) для любого m(x) делится без остатка на g(x).
Из этого свойства положим следующий алгоритм декодирования

1. Принятое сообщение $\overline{b} = \overline{a} + \overline{e}$, где e - вектор ошибок
2. Вычислим синдром $s(x)=b(x)\mod{g(x)}$
3. Если s(x) != 0, то декодер выносит решение, что произошли ошибки (E = 1), иначе ошибок не произошло (E = 0).



**ENG**

Only binary codes are considered, polynomials with coefficients from GF(2) are used
Notation
- g(x) - generating polynomial
- r = deg(g(x)) - degree of the generating polynomial, which determines the number of bits of the checksum in the codeword.
- k - number of information symbols of the transmitted message $\overline{m}$

The transmitted message is a vector of length k
For each message ($\overline{m}$), the encoder performs:
1. Forms m(x) based on $\overline{m}$, $deg(m(x)) \underline{<} k-1$
2. Calculates $c(x) = m(x) * x^r \mod{g(x)}$, $deg(c(x)) \underline{<} r-1$
3. Computes the polynomial $a(x) = m(x) * x^r + c(x)$
4. Based on the polynomial a(x), forms a vector $\overline{a}$ , whose length is n bits, where n = k + r.

Example of coder operation:
0. $g(x) = x^3 + x + 1 , deg(g(x)) = 3$
1. $\overline{m}=1010, k=4$; $m(x)=1x^3 +0x^2 + 1x +0x^0$
2. $c(x)=(x^3+x)x^3 \mod{(x^3 + x + 1)} = x+1$
3. $a(x)=(x^3+x)x^3 + x + 1=x^6+x^4+x+1$
4. $\overline{a}=1010011, n=4+3=7$

Note that a(x) is divisible without remainder by g(x) for any m(x).
From this property, let us posit the following decoding algorithm

1. The received message $\overline{b} = \overline{a} + \overline{e}$, where e is the error vector
2. Let us compute the syndrome $s(x)=b(x)\mod{g(x)}$
3. If s(x) != 0, the decoder decides that errors have occurred (E = 1), otherwise no errors have occurred (E = 0).
