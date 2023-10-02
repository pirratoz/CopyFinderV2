print("Hello World!")
!

class User:
    def __init__(self, name: str, age: int) -> None:
        self.name = name
        self.age = age

    def say_hello(self) -> None:
        print(f"Hello, i'm user {self.name} and i'm {self.age}")


class Worker(User):
    def __init__(self, name: str, age: int, sallary: int) -> None:
        super().__init__(name, age)
        self.sallary = sallary

    def say_hello(self) -> None:
        print(f"Hello, i'm worker {self.name} and i'm {self.age}")


user_1 = User("Kirill", 15)
user_2 = Worker("Oleg", 18, -666)

user_1.say_hello()
user_2.say_hello()
