import std.stdio;

class Matrix
{
        private: 
        char name;

        int width;
        int height;
        
        int[][] self;
        
        public:
        
        void
        set_dimensions()
        {
                this.width = readln();
                this.height = readln();
        }
}

void 
main()
{
        printf("Hello, world!");
}