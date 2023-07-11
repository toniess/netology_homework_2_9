#include <iostream>

class Fraction
{
private:
	int numerator_;
	int denominator_;

public:
	Fraction(const int numerator, const int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}

	bool operator==(const Fraction& rhs) const
	{
		return this->numerator_ * rhs.denominator_ == this->denominator_ * rhs.numerator_;
	}
	bool operator!=(const Fraction& rhs) const
	{
		return !(*this == rhs);
	}
	bool operator>(const Fraction& rhs) const
	{
		return this->numerator_ * rhs.denominator_ > this->denominator_ * rhs.numerator_;
	}
	bool operator<=(const Fraction& rhs) const
	{
		return !(*this > rhs);
	}
	bool operator<(const Fraction& rhs) const
	{
		return !(*this > rhs) && (*this != rhs);
	}
	bool operator>=(const Fraction& rhs) const
	{
		return !(*this < rhs);
	}

	Fraction operator+(const Fraction& rhs) const
	{
		Fraction f(this->numerator_ * rhs.denominator_ + this->denominator_ * rhs.numerator_,
						this->denominator_ * rhs.denominator_);
		f.shorten();
		return f;
	}
	Fraction operator-(const Fraction& rhs) const
	{
		Fraction f(this->numerator_ * rhs.denominator_ - this->denominator_ * rhs.numerator_,
			this->denominator_ * rhs.denominator_);
		f.shorten();
		return f;
	}
	Fraction operator*(const Fraction& rhs) const
	{
		Fraction f(this->numerator_ * rhs.numerator_,
			this->denominator_ * rhs.denominator_);
		f.shorten();
		return f;
	}
	Fraction operator/(const Fraction& rhs) const
	{
		Fraction f(this->numerator_ * rhs.denominator_,
			this->denominator_ * rhs.numerator_);
		f.shorten();
		return f;
	}
	Fraction operator-() const
	{
		if (this->numerator_ * this->denominator_ >= 0)
		{
			return Fraction(this->numerator_ * -1, this->denominator_);
		}
		else
		{
			return Fraction(abs(this->numerator_), abs(this->denominator_));
		}	
	}
	Fraction& operator++()
	{
		this->numerator_ += this->denominator_;
		this->shorten();
		return *this;
	}
	Fraction& operator--()
	{
		this->numerator_ -= this->denominator_;
		this->shorten();
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction tmp(*this);
		++(*this);
		return tmp;
	}
	Fraction operator--(int)
	{
		Fraction tmp(*this);
		--(*this);
		return tmp;
	}

	void shorten()
	{
		long tnum, tden, gcd;
		tnum = labs(numerator_);
		tden = labs(denominator_);
		if (tnum == 0)
		{
			numerator_ = 0; 
			denominator_ = 1; return;
		}
		while (tnum != 0)
		{
			if (tnum < tden)
			{
				std::swap(tnum, tden);
			}
			tnum = tnum - tden;
		}
		gcd = tden;
		numerator_ /= gcd;
		denominator_ /= gcd;
	}
	friend std::ostream& operator<<(std::ostream& cout, const Fraction& f);
};

std::ostream& operator<<(std::ostream& cout, const Fraction& f)
{
	return cout << f.numerator_ << "/" << f.denominator_;
}

int main()
{
	{
		Fraction f1(4, 3);
		Fraction f2(6, 11);

		std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
		std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
		std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
		std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
		std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
		std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';
	}
	{
		setlocale(LC_ALL, "rus");
		int n, d;
		std::cout << "¬ведите числитель дроби 1: ";
		std::cin >> n;
		std::cout << "¬ведите знаменатель дроби 1: ";
		std::cin >> d;
		Fraction f1(n, d);
		std::cout << "¬ведите числитель дроби 2: ";
		std::cin >> n;
		std::cout << "¬ведите знаменатель дроби 2: ";
		std::cin >> d;
		Fraction f2(n, d);
		std::cout << f1 << " + " << f2 << " = " << f1 + f2 << std::endl;
		std::cout << f1 << " - " << f2 << " = " << f1 - f2 << std::endl;
		std::cout << f1 << " * " << f2 << " = " << f1 * f2 << std::endl;
		std::cout << f1 << " / " << f2 << " = " << f1 / f2 << std::endl;

		std::cout << "++" << f1 << " * " << f2 << " = " << ++f1 * f2 << std::endl;
		std::cout << "«начение дроби 1 = " << f1 << std::endl;

		std::cout << f1 << "-- * " << f2 << " = " << f1-- * f2 << std::endl;
		std::cout << "«начение дроби 1 = " << f1 << std::endl;
	}
}