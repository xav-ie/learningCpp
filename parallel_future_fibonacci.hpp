#ifndef parallel_future_fibonacci_hpp
#define parallel_future_fibonacci_hpp

template<typename value_t, typename index_t>
void parallel_future_fibonacci(value_t n, value_t * result) {
        value_t a_0 = 0;
        value_t a_1 = 1;
        for(index_t index = 0; index < n; ++index) {
                const value_t tmp = a_0; a_0 = a_1; a_1+=tmp;
        }
        *result = a_0;
}


#endif
