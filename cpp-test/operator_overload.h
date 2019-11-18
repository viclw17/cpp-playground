class Person{
	private:
		int age;
	public:
		Person(int a){
			this->age = a; // access member variable via pointer		
		}
		inline bool operator == (const Person& ps) const;
};

inline bool Person::operator == (const Person& ps) const{
	if(this->age == ps.age)
		return true;
	return false;
}
