#include <iostream>
#include <string.h>
using namespace std;

class Customer
{
public:
	int id;
	int timeEntry;
	int transactionPeriod;
	Customer *prev;
	Customer *next;

	Customer() {
		id = timeEntry = transactionPeriod = 0;
		prev = next = NULL;
	}

	void Display() {
		cout << "ID: " << this->id;
		cout << "\nEntry Time: " << this->timeEntry;
		cout << "\nTransaction Period: " << this->transactionPeriod << "\n\n";
	}
};



class Queue
{
public:
	Customer *front;
	Customer *rear;
	int currentCount, totalCustomerCount, totalCustomerTransation, totalWaitingTime;
	int flag;

	Queue() {
		front = rear = NULL;
		currentCount = totalCustomerCount = totalCustomerTransation = totalWaitingTime = 0;
		flag = 0;
	}

	bool isEmpty()
	{
		return front == NULL;
	}

	void Enqueue(Customer *cust)
	{
		totalCustomerTransation += cust->transactionPeriod;

		Customer *current = front;
		if (currentCount == 0) {
			totalWaitingTime += 0;
		}
		else if (flag) {
			for (int i = 0; i < currentCount; i++)
			{
				totalWaitingTime += current->transactionPeriod;
				current = current->next;
			}
			flag = 0;
		}
		else {
			for (int i = 0; i < currentCount; i++)
			{
				if (i == 0) {
					totalWaitingTime += front->transactionPeriod - (cust->timeEntry - front->timeEntry);
				}
				else {
					totalWaitingTime += current->transactionPeriod;
				}
				current = current->next;
			}
		}

		if (front == NULL)
		{
			
			cust->prev = cust->next = NULL;
			front = rear = cust;
		}
		else
		{
			
			cust->prev = cust->next = NULL;
			rear->prev = NULL;
			rear->next = cust;
			rear = cust;
		}
		currentCount++;
		totalCustomerCount++;
		
	}

	Customer* Dequeue()
	{
		if (front != NULL) {
			
			Customer* temp = front;
			front = front->next;
			currentCount--;
			return temp;
		}
	}

	void EmptyWindow(int newCustTimeEntry) {
		int flagEnter = 1;
		flag = 0;
		while (front != NULL && flagEnter)
		{
			if (front->transactionPeriod <= (newCustTimeEntry - front->timeEntry)) {
				if (front->transactionPeriod == (newCustTimeEntry - front->timeEntry)) {
					flag = 1;
				}
				Dequeue();
				//current = front->next;
				flagEnter = 1;
			}
			else {
				flagEnter = 0;
			}
		}
	}
};

class LinkedListed
{
public:
	Customer *first;
	Customer *last;

	LinkedListed() {
		first = last = NULL;
	}

	Customer* Create(int id, int timeEntry, int transactionPeriod)
	{
		Customer *new_cust = new Customer();
		new_cust->id = id;
		new_cust->timeEntry = timeEntry;
		new_cust->transactionPeriod = transactionPeriod;
		new_cust->prev = new_cust->next = NULL;
		return new_cust;
	}

	void Add(Customer *new_cust) {
		if (first == NULL)
		{
			first = last = new_cust;
		}
		else
		{
			last->next = new_cust;
			new_cust->prev = last;
			new_cust->next = NULL;
			last = new_cust;
		}
	}

	Customer* Search(Customer* cust) {
		Customer *current = first;
		while (current != NULL)
		{
			if (current->id == cust->id)
			{
				return current;
			}
			current = current->next;
		}
		return NULL;
	}

	LinkedListed* SearchAll(Customer* cust)
	{
		Customer *current = first;
		LinkedListed *list = new LinkedListed();

		while (current != NULL)
		{
			if (current->id == cust->id)
			{
				list->Add(current);
			}
			current = current->next;
		}
		return list;
	}

	void InsertionBefore(Customer *before, Customer *new_cust)
	{
		if (before->prev == NULL)
		{
			new_cust->prev = NULL;
			new_cust->next = before;
			first = new_cust;
			before->prev = new_cust;
		}
		else
		{
			new_cust->prev = before->prev;
			new_cust->next = new_cust->prev->next;
			before->prev->next = new_cust;
			before->prev = new_cust;
		}
	}

	void InsertionAfter(Customer *after, Customer *new_cust)
	{
		if (last == after)
		{
			Add(new_cust);
		}
		else
		{
			new_cust->prev = after;
			new_cust->next = after->next;
			after->next->prev = new_cust;
			after->next = new_cust;
		}
	}

	bool isEmpty() {
		return first == NULL;
	}

	Customer* Deletion() {
		Customer *cust = first;
		if (first == last)
		{
			first = last = NULL;
		}
		else
		{
			first = first->next;
		}

		return cust;
	}

	void Deletion(Customer* new_cust)
	{
		if (first == new_cust)
		{
			if (first == last)
			{
				first = last = NULL;
			}
			else
			{
				first = first->next;
			}
		}
		else if (last == new_cust)
		{
			last->prev->next = NULL;
			last = last->prev;
		}
		else
		{
			new_cust->prev->next = new_cust->next;
			new_cust->next->prev = new_cust->prev;
		}
		new_cust->prev = new_cust->next = NULL;
	}

	void DisplayAll() {
		Customer *current = first;
		while (current != NULL)
		{
			cout << "\nID:" << current->id << "\n";
			cout << "Entry Time:" << current->timeEntry << "\n";
			cout << "Transaction Period:" << current->transactionPeriod << "\n";
			current = current->next;
		}
	}
};

void BubbleSort(LinkedListed *list) {
	int isSorted;
	Customer *cust = list->first;
	do {
		isSorted = 1;
		while (cust->next != NULL) {
			if (cust->timeEntry > cust->next->timeEntry) {
				int tempID = cust->next->id;
				int tempEntry = cust->next->timeEntry;
				int tempPeriod = cust->next->transactionPeriod;
				Customer *tempNextCust = cust->next->next;
				if (cust == list->first) {
					
					list->Deletion(cust->next);
					cust->next = tempNextCust;
					Customer *new_cust = list->Create(tempID, tempEntry, tempPeriod);
					list->InsertionBefore(cust, new_cust);
				}
				
				else {
					
					list->Deletion(cust->next);
					cust->next = tempNextCust;
					Customer *new_cust = list->Create(tempID, tempEntry, tempPeriod);
					list->InsertionBefore(cust, new_cust);
				}
				isSorted = 0;
			}
			
			else
			{
				cust = cust->next;
			}
		}
		cust = list->first;
	} while (!isSorted);
}

int main() {
	LinkedListed *enteredCustomers = new LinkedListed();

	char *answer = new char[4];
	do
	{
		cout << "Do you want to enter a new customer ? yes or no : ";
		cin >> answer;
		if (strcmp(answer, "no") != 0) {
			Customer *cust = new Customer();
			cout << "Enter ID: ";
			cin >> cust->id;
			cout << "Enter Entry Time: ";
			cin >> cust->timeEntry;
			cout << "Enter Transaction Period: ";
			cin >> cust->transactionPeriod;
			enteredCustomers->Add(cust);
		}
		else
		{
			cout << "Thanks for using my App\n\n";
		}
	} while (strcmp(answer, "no"));

	cout << "----------------------------------- Before Sorting --------------------------------------------- \n";
	enteredCustomers->DisplayAll();
	BubbleSort(enteredCustomers);
	cout << "----------------------------------- After Sorting --------------------------------------------- \n";
	enteredCustomers->DisplayAll();

	Queue *window1 = new Queue();
	Queue *window2 = new Queue();
	Queue *window3 = new Queue();

	while (!enteredCustomers->isEmpty())
	{
		
		Customer *newCust = enteredCustomers->Deletion();
		window1->EmptyWindow(newCust->timeEntry);
		window2->EmptyWindow(newCust->timeEntry);
		window3->EmptyWindow(newCust->timeEntry);
		if (window1->currentCount <= window2->currentCount && window1->currentCount <= window3->currentCount) {
			window1->Enqueue(newCust);
		}
		else if (window2->currentCount <= window1->currentCount && window2->currentCount <= window3->currentCount) {
			window2->Enqueue(newCust);
		}
		else {
			//window3->Enqueue(enteredCustomers->Deletion());
			window3->Enqueue(newCust);
		}
	}

	cout << "-------------------------------------------------- Window 1 ----------------------------------------\n";
	while (!window1->isEmpty())
	{
		Customer *cust = window1->Dequeue();
		cust->Display();
	}
	cout << "\nTotal Customer Count: " << window1->totalCustomerCount;
	cout << "\nTotal Customer Transactions: " << window1->totalCustomerTransation;
	cout << "\nWindow Performance: " << (float)window1->totalCustomerTransation / window1->totalCustomerCount;
	cout << "\nTotal Waiting Time: " << window1->totalWaitingTime;
	cout << "\n-------------------------------------------------- Window 2 ----------------------------------------\n";
	while (!window2->isEmpty())
	{
		Customer *cust = window2->Dequeue();
		cust->Display();
	}
	cout << "\nTotal Customer Count: " << window2->totalCustomerCount;
	cout << "\nTotal Customer Transactions: " << window2->totalCustomerTransation;
	cout << "\nWindow Performance: " << (float)window2->totalCustomerTransation / window2->totalCustomerCount;
	cout << "\nTotal Waiting Time: " << window2->totalWaitingTime;
	cout << "\n-------------------------------------------------- Window 3 ----------------------------------------\n";
	while (!window3->isEmpty())
	{
		Customer *cust = window3->Dequeue();
		cust->Display();
	}
	cout << "\nTotal Customer Count: " << window3->totalCustomerCount;
	cout << "\nTotal Customer Transactions: " << window3->totalCustomerTransation;
	cout << "\nWindow Performance: " << (float)window3->totalCustomerTransation / window3->totalCustomerCount;
	cout << "\nTotal Waiting Time: " << window3->totalWaitingTime;
	cout << "\n\n";

	int totalCustomers = window1->totalCustomerCount + window2->totalCustomerCount + window3->totalCustomerCount;
	int totalTransactions = window1->totalCustomerTransation + window2->totalCustomerTransation + window3->totalCustomerTransation;
	cout << "\nTotal Customers: " << totalCustomers;
	cout << "\nTotal Transactions: " << totalTransactions;
	cout << "\nAverage Transaction Time: " << (float)totalTransactions / totalCustomers;
	cout << "\nTotal Waiting Time for All: " << window1->totalWaitingTime + window2->totalWaitingTime + window3->totalWaitingTime;
	
	
	system("pause");
	return 0;
}