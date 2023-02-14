template <typename T>
struct Vect2D {

    T x, y;

    Vect2D() {
        x = 0;
        y = 0;
    }

    Vect2D(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

    //Addition v1 + v2
    inline Vect2D<T> operator+ (const Vect2D<T>& v2) const {
        return Vect2D<T>(x + v2.x, y + v2.y);
    }

    //Addition assigment v1 += v2
    inline friend Vect2D<T>& operator+=(Vect2D<T>& v1, const Vect2D<T>& v2)
    {
        v1.x += v2.x;
        v1.y += v2.y;
        return v1;
    }

    //Substraction v1 - v2
    inline Vect2D<T> operator-(const Vect2D<T>& v2) const {
        return Vect2D<T>(x - v2.x, y - v2.y);
    }

    //Subsraction assigment v1 -= v2
    inline friend Vect2D<T>& operator -=(Vect2D<T>& v1, const Vect2D<T>& v2) {
        v1.x -= v2.x;
        v1.y -= v2.y;
        return v1;
    }

    //multiplication v * f
    inline Vect2D<T> operator*(const T scalar) const {
        return Vect2D<T>(x * scalar, y * scalar);
    }

    //division v/d
    inline Vect2D<T> operator/(const T d)const {
        return (d != 0 ? Vect2D<T>(x / d, y / d) : Vect2D<T>());
    }

    inline Vect2D<T>& zero() {
        this->x = 0;
        this->y = 0;
        return *this;
    }

    inline Vect2D<T>& ones() {
        this->x = 1;
        this->y = 1;
        return *this;
    }

    inline friend std::ostream& operator<<(std::ostream& stream, const Vect2D<T>& v)
    {
        stream << "(" << v.x << "," << v.y << ")";
        return stream;
    }
};

using Vect2I = Vect2D<int>;
using Vect2U = Vect2D<unsigned int>;
using Vect2F = Vect2D<float>;
using Vect2LF = Vect2D<double>;
