#ifndef MINUTIAE_H
#define MINUTIAE_H


class Minutiae
{
    public:
        enum Type {BIFURCATION, RIDGEENDING};
        Minutiae(int locX, int locY, Type type);
        virtual ~Minutiae();
        int getLocX();
        int getLocY();
        Type getType();
        void setMarkTrue();
        bool getMark();
    protected:
    private:
        int locX;
        int locY;
        Type type;
        bool markedForErasing;

};

#endif // MINUTIAE_H
