#ifndef AMA_AMAAPP_H
#define AMA_AMAAPP_H

#include "iProduct.h"

namespace ama {
	const int m_products_size (100);
	const int m_filename_length(256);
	class AmaApp {
		char m_filename[m_filename_length];
		iProduct* m_products[m_products_size];
		int m_noOfProducts;
		AmaApp(const AmaApp&) = delete;		//assignment prohibited
		AmaApp& operator=(const AmaApp&) = delete;		//copy prohibited
		void pause() const;		//pause the console
		int menu() const;		//displays menu
		void loadProductRecords();	//load product data from file
		void saveProductRecords()const;	//writes data from m_products to file
		void listProducts()const;		//display product info into console	
		void printTitle()const;			//prints report title
		void printFooter(double totalCost)const;		//prints report footer
		iProduct* find(const char * skuToFind)const;	//finds the sku in the array
		void addQty(iProduct* product);				//adds to quantity on hand
		void addProduct(char tag);					//add new product to the m_products array
		const char* getSKUfromUser(char* )const;				//this function take SKU input from user 
		void deleteElements();
	public:
		AmaApp(const char fileName[]);
		~AmaApp();
		int run();
	};


}


#endif