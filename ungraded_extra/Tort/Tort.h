#ifndef TORT_H_INCLUDED
#define TORT_H_INCLUDED

class Ratio {
  public:
    Ratio(int num = 0, int den = 1);
    int num() const { return num_; }
    int den() const { return den_; }
    operator double() const;
    //Ratio& operator+=(Ratio r);
    Ratio& operator-=(Ratio r);
    Ratio& operator*=(Ratio r);
    Ratio& operator/=(Ratio r);
  private:
    int num_;
    int den_;
};


#endif // TORT_H_INCLUDED
