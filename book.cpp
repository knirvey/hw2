#include "book.h"
#include "util.h"
#include <sstream>

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string& isbn, const std::string& author)
      :Product(category, name, price, qty), isbn_(isbn), author_(author){}
Book:: ~Book() {}

std::set<std::string> Book::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_);
  std::set<std::string> authorWords = parseStringToWords(author_);
  keys.insert(authorWords.begin(), authorWords.end());
  keys.insert(isbn_);
  return keys;
}

std::string Book::displayString() const{
  std::ostringstream os;
  os<<name_<<"\n"
  <<"Author: "<<author_<<" ISBN: "<<isbn_<<"\n"
  <<price_<<" "<<qty_<<" left.";

  return os.str();
  
}


void Book::dump(std::ostream& os) const{
  os<<"book\n" << name_<<"\n"<<price_<<"\n"<<qty_<<"\n"<<isbn_<<"\n"<< author_<<std::endl;
}