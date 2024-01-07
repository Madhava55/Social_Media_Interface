#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <stack>
#include <utility>
using namespace std;
class post;
class account
{
public:
    string name;
    string profile;
    vector<post> mypost;
    account(){}
    account(string name1) { name = name1; }
    void editprofile(string newprofile)
    {
        profile = newprofile;
    }
    void newpost(string post_title, string newpost1);
    bool operator<(const account& other) const {
        return name < other.name;
    }
    bool operator==(const account& other) const {
    return name == other.name;
}
};
map<account, vector<account>> following;
class post
{
public:
    string input_post;
    vector<account> person;
    vector<string> comment;
    string post_title;
    vector<bool> like;
    post(){}
    post(string input_post1, string post_title1):person(), like()
    {
        input_post = input_post1;
        post_title = post_title1;
    }
    void edit(account person1, bool like1 = false, string comment1 = "")
    {
        if (find(person.begin(), person.end(), person1) == person.end())
        {
            person.push_back(person1);
            comment.push_back(comment1);
            like.push_back(like1);
        }
    }
    void show()
    {
        for (size_t i = 0; i < person.size(); i++)
        {
            if (like[i] == false)
                cout << person[i].name << " has commented --> " << comment[i] << "." << endl;
            else if (comment[i] == "")
                cout << person[i].name << " has liked the post." << endl;
            else
                cout << person[i].name << " has liked the post and commented --> " << comment[i] << "." << endl;
        }
    }
    
};
void account::newpost(string post_title, string newpost1)
    {
        mypost.push_back(post(newpost1, post_title));
    }
stack<pair<account, post>> feed_db;

void like_comment_post(account myaccount, account person1, string post_title1, bool like, string comment)
{
    for (size_t i = 0; i< person1.mypost.size(); i++)
    {
        if (person1.mypost[i].post_title == post_title1)
        {
            person1.mypost[i].edit(myaccount, like, comment);
        }
    }
}
void follow(account myaccount, account person1)
{
    following[myaccount].push_back(person1);
}
void unfollow(account myaccount, account person1)
{
    following[myaccount].erase(find(following[myaccount].begin(), following[myaccount].end(), person1));
}
void feed(account myaccount)
{
    stack<pair<account, post>> feed_dbt = feed_db;
    while (!feed_dbt.empty())
    {
        if (find(following[myaccount].begin(), following[myaccount].end(), feed_dbt.top().first) != following[myaccount].end())
        { 
            cout << following[myaccount][find(following[myaccount].begin(), following[myaccount].end(), feed_dbt.top().first) - following[myaccount].begin()].name << " had posted a post titled " << feed_dbt.top().second.post_title << " saying --> " << feed_dbt.top().second.input_post << endl;
        }
        feed_dbt.pop();
    }
}
unordered_map<string, account> all_accounts;
int main()
{
    string present_acc;
    string start="stop";
    cout << "Welcome to MaddyChat. This is a demo social media app I have made...will be adding more features later on... :)" << endl;
    cout << "Type start to start the program and stop to end the program" << endl;
    cin >> start;
    cin.ignore();
    cout << "Please command" << endl;
    while (start != "stop")
    {
        string command;
        getline(cin,command);
        if (command == "login")
        {
            cout << "Pls enter account name" << endl;
            getline(cin,command);
            if (all_accounts.find(command) != all_accounts.end())
            {
                cout << "Logging in..." << endl;
                present_acc = command;
            }
            else{
                cout<<"sorry...no such account exists..."<<endl;
            }
        }
        else if (command == "new account")
        {
            cout<<"enter your name"<<endl;
            string name;
            getline(cin,name);
            account new_account(name);
            all_accounts.insert({name, new_account});
            cout << "Account created successfully!...you can login now..." << endl;
        }
        else if (command == "follow")
        {
            cout << "Enter the person to follow..." << endl;
            getline(cin,command);
            follow(all_accounts[present_acc], all_accounts[command]);
        }
        else if (command == "unfollow")
        {
            cout << "Enter the person to unfollow..." << endl;
            getline(cin,command);
            unfollow(all_accounts[present_acc], all_accounts[command]);
        }
        else if (command == "like or comment")
        {
            cout << "Enter the person's name and the post name you want to like or comment" << endl;
            string person_now;
            getline(cin,person_now);
            string title_now;
            getline(cin,title_now);
            cout << "Enter 1 if you want to like a post..." << endl;
            bool like_now = false;
            cin >> like_now;
            cout << "Type any comment you would wish to post else press enter..." << endl;
            string comment_now;
            getline(cin,comment_now);
            like_comment_post(all_accounts[present_acc], all_accounts[person_now], title_now, like_now, comment_now);
        }
        else if (command == "new post")
        {
            cout << "Enter the post title..." << endl;
            getline(cin,command);
            cout << "type your post..." << endl;
            string para;
            getline(cin,para);
            post new_post(para, command);
            feed_db.push(make_pair(all_accounts[present_acc], new_post));
            all_accounts[present_acc].newpost(para, command);
            all_accounts[present_acc].newpost(command, para);
        }
        else if (command == "feed")
        {
            cout << "Here you go..." << endl;
            feed(all_accounts[present_acc]);
        }
        else if (command == "edit profile")
        {
            cout << "Type your new bio here..." << endl;
            getline(cin,command);
            all_accounts[present_acc].editprofile(command);
        }
        else if (command == "exit")
        {
            cout << "Please type stop..." << endl;
            cin >> start;
        }
        else if (command == "show comments and likes")
        {
            cout << "Please enter account name and post name" << endl;
            getline(cin,command);
            string post_check;
            getline(cin,post_check);
            for (size_t i=0;i<all_accounts[command].mypost.size();i++) 
            {
                if(all_accounts[command].mypost[i].post_title==post_check)
                {
                    all_accounts[command].mypost[i].show();
                }
            }
        }
        else
        {
            cout << "Invalid instruction...please type again..." << endl;
        }
    }
    cout<<"Thank you for choosing our app for your leisure"<<endl;
    return 0;
}
