#include <iostream>
#include <vector>
#include <memory>
using namespace std;

namespace ariel{
template<typename T>
class BinaryTree{

    // Inner class for Binary Tree - Node.
    class BTNode{
    public:
    T data;
    BTNode* father;
    BTNode* left;
    BTNode* right;
    BTNode(T data): data{data},left{nullptr},right{nullptr},father{nullptr}{};
    void set_val(T& new_data){this->data=new_data;}
    friend ostream& operator<<(ostream& output, BTNode& other){
        output << other.data;
        return output;
    }
    };

    // Binary Tree Class members.
    BTNode* root;
    unsigned int ptr_num=1;
    unsigned int size=0;
    vector<BinaryTree*> shallow_copies;
    public:

    BinaryTree():root{nullptr},size{0},ptr_num{1}{}
    BinaryTree(BinaryTree&& other)noexcept{
        if(this!=&other){
            this->size=other.size;
            this->ptr_num=other.ptr_num;
            for(auto tree: other.shallow_copies){
                this->shallow_copies.push_back(tree);
            }
            this->root=other.root;
            other.size=0;
            this->ptr_num=1;
            other.shallow_copies.clear();
            other.root=nullptr;
        }
    }
    BinaryTree& operator=(BinaryTree&& other) noexcept{
        if(*this==&other){return *this;}
        if(root!=nullptr){delete_tree(root);}
        this->size=other.size;
        this->ptr_num=other.ptr_num;
        for(auto tree: other.shallow_copies){
            this->shallow_copies.push_back(tree);
        }
        this->root=other.root;
        other.size=0;
        this->ptr_num=1;
        other.shallow_copies.clear();
        other.root=nullptr;
        return *this;  
    }
    BinaryTree& add_root(T new_root){
        if(root==nullptr){ root = new BTNode(new_root); ptr_num=1; size=1;}
        else{root->set_val(new_root);}
        return *this;
    }
    void copy_tree(const BTNode* original,BTNode*& copy,BTNode*& prev,bool isRight){
        if (original==nullptr){ return;}
        copy=new BTNode(original->data);
        copy->father=prev;
        if(prev!=nullptr){
            if(isRight){
                copy->father->right=copy;
            }else{
                copy->father->left=copy;
            }
        }
        if(original->left!=nullptr){
            BTNode* left_son=nullptr;
            copy_tree(original->left,left_son,copy,false);
        }
        if(original->right!=nullptr){
            BTNode* right_son=nullptr;
            copy_tree(original->right,right_son,copy,true);
        }
    }
    BinaryTree(BinaryTree& other){
        if(this!=&other){
            BTNode* temp=nullptr;
            if(other.root!=nullptr) {copy_tree(other.root,this->root,temp,false);}
            this->size=other.size;
            this->ptr_num=other.ptr_num;
            this->shallow_copies.clear();
            for(auto num: other.shallow_copies){
                this->shallow_copies.push_back(num);
            }
        }
    }

    BinaryTree& operator=(BinaryTree other){
        if(this==&other){return *this;}
        if(root!=nullptr){delete_tree(root);}
        this->root=nullptr;
        BTNode* temp=nullptr;
        if(other.root!=nullptr) {copy_tree(other.root,this->root,temp,false);}
        this->size=other.size;
        this->ptr_num=other.ptr_num;
        this->shallow_copies.clear();
        for(auto tree: other.shallow_copies){
            this->shallow_copies.push_back(tree);
        }
        return *this;
    }

    // Class  iterator inorder.
    class iterator_in{
        private:
        unsigned int cur_index;
        unsigned int size;
        unsigned int index;
        BTNode* cur;
        BTNode* root;
        void find_in(BTNode*& root){
            if(root==nullptr) {return;}
            find_in(root->left);
            cur_index++;
            if(cur_index==index){ cur=root; return;}
            find_in(root->right);
        }   
        public:
        iterator_in(unsigned int index,unsigned int size,BTNode*& root):index{index},cur{nullptr},size{size},root{root}{
            if(index<=size){cur_index=0; find_in(root);}
        }
        T& operator*() const {
            return cur->data;
		}
        T* operator->() const {
            return &(cur->data);
		}
        iterator_in& operator++() {
            index++;
            cur_index=0;
            find_in(root);
            return *this;
		}
        iterator_in operator++(int) {
			iterator_in tmp= *this;
			index++;
            cur_index=0;
            find_in(root);
            return tmp;
		}
        bool operator==(const iterator_in& other) const {
			return index == other.index;
		}

		bool operator!=(const iterator_in& other) const {
			return index!=other.index;
		}
    };
    
    // Class  iterator postorder.
    class iterator_post{
        private:
        unsigned int cur_index;
        unsigned int size;
        unsigned int index;
        BTNode* cur;
        BTNode* root;
        void find_post(BTNode*& root){
            if(root==nullptr) {return;}
            find_post(root->left);
            find_post(root->right);
            cur_index++;
            if(cur_index==index){ cur=root; return;}
        }   
        public:
        iterator_post(unsigned int index,unsigned int size,BTNode*& root):index{index},cur{nullptr},size{size},root{root}{
            if(index<=size){ cur_index=0; find_post(root);}
        }
        T& operator*() const {
            return cur->data;
		}
        T* operator->() const {
            return &(cur->data);
		}
        iterator_post& operator++() {
            index++;
            cur_index=0;
            find_post(root);
            return *this;
		}
        iterator_post operator++(int) {
			iterator_post tmp= *this;
			index++;
            cur_index=0;
            find_post(root);
            return tmp;
		}
        bool operator==(const iterator_post& other) const {
			return index == other.index;
		}

		bool operator!=(const iterator_post& other) const {
			return index!=other.index;
		}
    };

    // Class  iterator preorder.
    class iterator_pre{
        private:
        unsigned int cur_index;
        unsigned int size;
        unsigned int index;
        BTNode* cur;
        BTNode* root;
        void find_pre(BTNode*& root){
            if(root==nullptr) {return;}
            cur_index++;
            if(cur_index==index){ cur=root; return;}
            find_pre(root->left);
            find_pre(root->right);
        }   
        public:
        iterator_pre(unsigned int index,unsigned int size,BTNode*& root):index{index},cur{nullptr},size{size},root{root}{
            if(index<=size){ cur_index=0; find_pre(root);}
        }
        T& operator*() const {
            return cur->data;
		}
        T* operator->() const {
            return &(cur->data);
		}
        iterator_pre& operator++() {
            index++;
            cur_index=0;
            find_pre(root);
            return *this;
		}
        iterator_pre operator++(int) {
			iterator_pre tmp= *this;
			index++;
            cur_index=0;
            find_pre(root);
            return tmp;
		}
        bool operator==(const iterator_pre& other) const {
			return index == other.index;
		}

		bool operator!=(const iterator_pre& other) const {
			return index!=other.index;
		}
    };

    
    iterator_in begin() {
		return iterator_in{1,size,root};
	}
    iterator_in end() {
		return iterator_in{size+1,size,root};
	}
    iterator_pre begin_preorder() {
		return iterator_pre{1,size,root};
	}
    iterator_pre end_preorder() {
		return iterator_pre{size+1,size,root};
	}
	iterator_in begin_inorder() {
        return begin();
	}
    iterator_in end_inorder() {
		return end();
	}
	iterator_post begin_postorder() {
		return iterator_post{1,size,root};
	}
    iterator_post end_postorder() {
		return iterator_post{size+1,size,root};
	}
    void printBT(const string& title,BTNode* root,bool isLeft,ostream& output){
        if(root==nullptr) {return;}
        output<<title;
        if(isLeft){
            output << "├──"; 
        }else{
            output << "└──";
        }
        output<< root->data << endl;
        printBT( title + (isLeft ? "│   " : "    "), root->left, true,output);
        printBT( title + (isLeft ? "│   " : "    "), root->right, false,output);
    }
    void printBT(ostream& output,BTNode* ptr){
        printBT("",ptr,false,output);
    }
    friend ostream& operator<<(ostream& output,BinaryTree& bt){
        bt.printBT(output,bt.root);
        return output;
    }

    private:
    void find(BTNode* node,BTNode*& temp,T& val){
        if(node==nullptr) {return;}
        if(node->data==val){ temp=node; return;}
        find(node->left,temp,val);
        find(node->right,temp,val);
    }
    public:
    BinaryTree& add_left(T father,T child){
        BTNode* temp=nullptr;
        find(root,temp,father);
        if(temp==nullptr) {throw out_of_range{"Error in add_left() function!"};}
        if(temp->left==nullptr){
            temp->left=new BTNode(child);
            temp->left->father=temp;
            size++;
        }else{
            temp->left->set_val(child);
        }
        return *this;
    }

    BinaryTree& add_right(T father,T child){
        BTNode* temp=nullptr;
        find(root,temp,father);
        if(temp==nullptr) {throw out_of_range{"Error in add_right() function!"};}
        if(temp->right==nullptr){
            temp->right=new BTNode(child);
            temp->right->father=temp;
            size++;
        }else{
            temp->right->set_val(child);
        }
        return *this;
    }
    void delete_tree(BTNode* root){
        if(root==nullptr) {return;}
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
    ~BinaryTree(){
        ptr_num--;
        if(ptr_num>0){
            for(auto tree : shallow_copies){
                tree->ptr_num=this->ptr_num;
            }         
            return;
        }
        delete_tree(root);
    }
};
};