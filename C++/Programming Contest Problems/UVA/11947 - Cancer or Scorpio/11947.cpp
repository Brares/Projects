// Jonathan Flores

#include <bits/stdc++.h>

using namespace std;
using namespace std::rel_ops;

struct Date {

  int yyyy;
  int mm;
  int dd;

  // no dates before 1753
  static int const BASE_YEAR = 1753;
  
  // Constructor to create a specific date.  If the date is invalid,
  // the behaviour is undefined
  Date(int yr = 1970, int mon = 1, int day = 1)
  {
    yyyy = yr;
    mm = mon;
    dd = day;
  }

  // Returns true if yr is a leap year
  static bool leapYear(int y)
  {
    return (y % 400 ==0 || (y % 4 == 0 && y % 100 != 0));
  }

  // number of days in this month
  static int daysIn(int m, int y)
  {
    switch (m) {
    case 4  :
    case 6  :
    case 9  :
    case 11 :
      return 30;
    case 2  :
      if (leapYear(y)) {
	return 29;
      }
      else {
	return 28;
      }
    default :
      return 31;
    }
  }

  void addDay(int n = 1)
  {
    dd += n;
    while (dd > daysIn(mm,yyyy)) {
      dd -= daysIn(mm,yyyy);
      if (++mm > 12) {
	mm = 1;
	yyyy++;
      }
    }
    
    while (dd < 1) {
      if (--mm < 1) {
	mm = 12;
	yyyy--;
      }
      dd += daysIn(mm,yyyy); 
    }
  }
};

// print date in mm/dd/yyyy format
ostream& operator<< (ostream &os, const Date &d) {
  char t = os.fill('0');
  os << setw(2) << d.mm << '/' << setw(2) << d.dd << '/' << d.yyyy;
  os.fill(t);
  return os;
}

int main() {
	int months[12] = {21,20,21,21,22,22,23,22,24,24,23,23}; 
	string zodiac[12] = {"aquarius", "pisces", "aries", "taurus", "gemini", "cancer", "leo", "virgo", "libra", "scorpio", "sagittarius", "capricorn"};
	int n = 0, counter = 0;
	cin >> n;
	cin.clear();
	cin.ignore();
	while (n--) {
		int index = 0;
		counter++;
		string sdate;
		getline(cin,sdate);
		int month = stoi(sdate.substr(0,2));
		int day = stoi(sdate.substr(2,2));
		int year = stoi(sdate.substr(4,4));	
		Date date(year, month, day);
		date.addDay(40*7);
		if (date.dd < months[date.mm - 1])
			if (date.mm == 1)
				index = 11;
			else
				index = date.mm - 2;
		else
			index = date.mm-1;
		cout << counter << " " << date << " " << zodiac[index] << endl;
	}
	return 0;
}
