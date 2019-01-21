/*Пара слов называется стековой анаграмой, если одно слово можно получить из другого,
проведя последовательность стековых операций с его буквами (взять очередную букву исходного слова и поместить ее в стек; 
взять букву из стека и добавить ее в конец выходного слова). 
Для заданной пары слов требуется определить, можно ли выполнить последовательность стековых операций, переводящую первое слово во второе. 
Все буквы в слове различные. Длина анаграммы ≤ 10000.*/
#include<bits/stdc++.h>
# define sz(s) int(s.size())
int main()
{
    std::string a, b;
    std::cin >> a >> b;
    if(sz(a) != sz(b)) std::cout << "NO";
    else {
        int left_b = 0;
		std::deque< char > deq;
        for(int i = 0, k = sz(a); i < k; i++){
            deq.push_back(a[i]);
            while((sz(deq) > 0) && (deq.back() == b[left_b])){
                left_b++;
                deq.pop_back();
            }
        }
        if(sz(deq) == 0) std::cout << "YES";
        else std::cout << "NO";
    }
    return 0;
}
