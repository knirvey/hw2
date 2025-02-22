#include "mydatastore.h"
#include "util.h"
#include <iostream>

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
  for(std::vector<Product*>::iterator it = products_.begin(); it!=products_.end(); it++) {
    delete *it;}
  for(std::map<std::string, User*>::iterator it=users_.begin(); it!= users_.end(); it++) {
    delete it->second;
}}

void MyDataStore::addProduct(Product* product){

  products_.push_back(product); //add a product 
  std::set<std::string> keywords= product->keywords();

  for(std::set<std::string>::iterator it= keywords.begin(); it!= keywords.end(); it++){
    std::string lowcapKey = convToLower(*it);
    keywordMap_[lowcapKey].insert(product); //storing product in keywordmap
  }

}

void MyDataStore::addUser(User* user){
  users_[convToLower(user->getName())] = user;
}

void MyDataStore::addCart(const std::string& username, Product* product){
  std::string lcapUser = convToLower(username);
  if(users_.find(lcapUser) == users_.end()){ //if user doesnt exist
    std::cout<<"Invalid request"<< std::endl;
    return;
  }

  userCarts_[lcapUser].push_back(product); //add the product to cart
  
}

void MyDataStore::viewCart(const std::string& username){
  std::string lcapUser= convToLower(username);
  if(users_.find(lcapUser) == users_.end()){ 
    std::cout<<"Invalid username"<< std::endl;
    return;
  }
  int itemNum = 1;
  for(std::vector<Product*>::iterator it=userCarts_[lcapUser].begin(); it!= userCarts_[lcapUser].end();it++){
    std::cout<<"Item "<<itemNum<<":"<<std::endl;
    std::cout<<(*it)->displayString() << std:: endl;
    std::cout<<std::endl;
    itemNum++;

  }
}

void MyDataStore::buyCart(const std::string& username){
  std::string lcapUser = convToLower(username);
  if(users_.find(lcapUser) == users_.end()){
    std::cout<<"Invalid username"<< std::endl;
    return;
  }

  std::vector<Product*>& cart=userCarts_[lcapUser];
  for(std::vector<Product*>::iterator it = cart.begin(); it!= cart.end();){
    Product* product = *it;
    if(product->getQty() >0 && users_[lcapUser]->getBalance() >= product->getPrice()){ //check if available and purchasable
     
      product->subtractQty(1); //subtracting stock number
      users_[lcapUser]->deductAmount(product->getPrice()); //deductAmount from user
      it = cart.erase(it);

    }else{
      it++;
    }

  }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  std::set<Product*> results; //search result
  bool processedFirst = false; //
  for(std::vector<std::string>::iterator it= terms.begin(); it!= terms.end(); it++){
   
    std::string lcapTerm = convToLower(*it);

    if(keywordMap_.find(lcapTerm) != keywordMap_.end()){
      std::set<Product*>& termResults = keywordMap_[lcapTerm];

      if(!processedFirst){ //initial valid keyword search
        results = termResults; //initializing the result set
        processedFirst = true;
      }
      else{
        if(type ==0){ //AND
          results = setIntersection(results, termResults);
            if(results.empty()){
              break;
          }
        }else{ //OR 
          results = setUnion(results, termResults);
        }
      }
    }
  }
  if(!processedFirst){ //no valid word given
    return std::vector<Product*>();
  }
  //return the result as vector
  return std::vector<Product*>(results.begin(), results.end());
}


void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << std::endl;
  for(std::vector<Product*>::iterator it=products_.begin(); it!= products_.end(); it++){
    (*it)->dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile <<"<users>" <<std::endl;
  for(std::map<std::string, User*>::iterator it = users_.begin(); it!= users_.end(); it++){
    it->second->dump(ofile);
  }
  ofile <<"</users>"<<std::endl;
}