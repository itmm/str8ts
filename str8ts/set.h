#if ! defined(set_h)
#define set_h

    #include <iostream>

    class set {
        public:
            set();
            set(int mask): _mask(mask) {}
        
            static set &forDigit(int digit);
        
            int popDigit();
        
            operator bool() { return _mask != 0; }
            set &operator|=(const set &s) { _mask |= s._mask; return *this; }
            set &operator&=(const set &s) { _mask &= s._mask; return *this; }
            set &operator-=(const set &s) { _mask &= ~s._mask; return *this; }
        
        private:
            int _mask;
    };

    std::ostream &operator<<(std::ostream &out, const set &s);

#endif /* set_h */
