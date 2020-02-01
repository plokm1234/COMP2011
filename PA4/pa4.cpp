/*
 * COMP2011 (Fall 2019) Assignment 4: The Web System
 * File: pa4.cpp
 *
 * Student name: YUEN WAI
 * Student ID: 20610033
 * Student email: wyuenab@ust.hk
 *
 * Note: This is for your implementation.
 * Please first fill your information above.
 * Feel free to add your helper functions in pa4.cpp.
 * There is no need to change other files.
 */

#include "web.h"
#include <vector>
#include <stack>

void help(const WebNode* root,const char* webAddress,const WebNode* &temp){
	for (int i = 0; i < root->numOfHyperlinks(); i++) {
	if (strcmp(root->hyperlink()[i]->webAddress(), webAddress) == 0) {temp=root;}
	}
}
void help2(const WebNode* root,vector<const WebNode*> &mnbv){
	if(root==nullptr){return;}
	mnbv.push_back(root);
	for (int i = 0; i < root->numOfHyperlinks(); i++) {help2(root->hyperlink()[i],mnbv);}
}

//task1
WebNode::WebNode(const char *webAddress, const char *anchorText, int height) {

	if (!isHTMLfile(webAddress)) { //non html file case
		m_webAddress = new char[strlen(webAddress) + 1];
		strcpy(m_webAddress, webAddress); //assign webaddress to the object
		m_anchorText = new char[strlen(anchorText) + 1];
		strcpy(m_anchorText, anchorText); //assign text to the object
		m_hyperlink = nullptr;
		m_numOfHyperlinks = 0;
	}

	else {
		m_webAddress = new char[strlen(webAddress) + 1];
		strcpy(m_webAddress, webAddress);
		m_anchorText = new char[strlen(anchorText) + 1];
		strcpy(m_anchorText, anchorText);

		if (height == 1) {
			m_hyperlink = nullptr;
			m_numOfHyperlinks = 0;
		}

		if (height > 1) {
			char **anchor_tag = nullptr;
			int num_tags = 0;
			extractAllAnchorTags(webAddress, anchor_tag, num_tags); //check how many links

			m_numOfHyperlinks = num_tags; //assign number of link to the object

			if (num_tags > 0) {
				m_hyperlink = new WebNode*[num_tags]; //create an array according to the number of link

				for (int i = 0; i < num_tags; i++) {
					const char* temp=getWebAddress(anchor_tag[i]);

					const char* temp1=getAnchorText(anchor_tag[i]);

					m_hyperlink[i] = new WebNode(temp, temp1,height - 1);

					delete[] temp;
					delete[] temp1;
					delete[] anchor_tag[i];
				}
				delete[] anchor_tag;
				anchor_tag = nullptr;
			} 
			else {
				m_hyperlink = nullptr;
			}
		}
	}
}
//task2
WebNode::~WebNode() {
	delete[] this->m_anchorText;
	delete[] this->m_webAddress;
	for(int i=0;i<m_numOfHyperlinks;i++){
		delete this->m_hyperlink[i];
	}
	delete[] m_hyperlink;
}
//task3
void WebNode::printGraph(int depth) const {
	for (int i = 0; i < depth; i++) {cout << "\t";}

	cout << anchorText() << " (url:" << webAddress() << ')' << endl;

	if (m_hyperlink != nullptr) {
		for (int i = 0; i < m_numOfHyperlinks; i++) 
		{m_hyperlink[i]->printGraph(depth + 1);}
	}
}
//task4
const WebNode* WebNode::findParent(const char *webAddress) const {
	vector <const WebNode*>zxcv;
	
	const WebNode* ujnh=nullptr;
	const WebNode* rtyu=nullptr;

	help2(this,zxcv);

	for(int i=zxcv.size();i-1>=0;i--){
			ujnh=zxcv[i-1];
			help(ujnh,webAddress,rtyu);
			if(rtyu!=nullptr)break;
	}
	return rtyu;
}
//task5
void WebNode::printPath(const char *address1, const char *address2) const {
		vector<string> abcd;

	if (strcmp(address2, address1) == 0) {
		cout << address2;
		return;
	}

	const WebNode *temp = findParent(address2);
	
	while (strcmp(m_webAddress,temp->m_webAddress)!=0) {
		abcd.push_back(temp->m_webAddress);
		if (strcmp(temp->m_webAddress, address1) == 0) {break;}
		temp = findParent(temp->m_webAddress);
	}

	if (strcmp(temp->m_webAddress, address1) == 0) {
		if(strcmp(address1,this->m_webAddress)==0){cout<<address1<<" ";}
		for (int i = abcd.size(); i - 1 >= 0; i--) {cout << abcd[i-1] << " ";}
		cout << address2;
	}
	else {cout << "Path not found";}
}
