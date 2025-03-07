#include "movie.h"
#include "util.h"
#include <sstream>

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string& genre, const std::string& rating)
      :Product(category, name, price, qty), genre_(genre), rating_(rating){}

Movie::~Movie(){}

std::set<std::string> Movie::keywords() const{
  std::set<std::string> keys=parseStringToWords(name_);
  keys.insert(genre_);
  return keys;
}

std::string Movie::displayString() const{
  std::ostringstream os;
  os<<name_<<"\n"
  <<"Genre: "<<genre_<<" Rating: "<<rating_<<"\n"
  <<price_<<" "<<qty_<<" left.";
return os.str();
}

void Movie::dump(std::ostream& os) const{
  os<<"movie\n" << name_<<"\n"<<price_<<"\n"<<qty_<<"\n"<<genre_<<"\n"<< rating_<<std::endl;

}