#if ! defined(game_h)
#define game_h

    #include <cstring>
    #include <iostream>

    class Game {
        private:
            char _data[9 * 9];
        
        public:
            Game(const char *data) { memcpy(_data, data, 9 * 9); }
            char operator()(int x, int y) const { return _data[y * 9 + x]; }
        
            char *free_cell();
            bool is_valid();
            bool is_complete();
        
        private:
            bool is_valid_row(const char *row, int offset);
    };

    inline bool is_free(char ch) { return ch == ' '; }
    inline bool is_blocked(char ch) {
        switch (ch) {
            case '#': case 'A': case 'B': case 'C': case 'D':
            case 'E': case 'F': case 'G': case 'H': case 'I':
                return true;
            default:
                return false;
        }
    }
    inline int digit(char ch) {
        switch (ch) {
            case '1': case 'A': return 1;
            case '2': case 'B': return 2;
            case '3': case 'C': return 3;
            case '4': case 'D': return 4;
            case '5': case 'E': return 5;
            case '6': case 'F': return 6;
            case '7': case 'G': return 7;
            case '8': case 'H': return 8;
            case '9': case 'I': return 9;
            default: return 0;
        }
    }
    inline char to_char(int digit) { return '0' + digit; }

    std::ostream &operator<<(std::ostream &out, const Game &game);

#endif
