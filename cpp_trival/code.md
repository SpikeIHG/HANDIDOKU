```cpp
void swap(Widget&lhs,Widget&rhs)
{
    std::swap(lhs.e1,rhs.e1);
    std::swap(lhs.e2,rhs.e2);
}

Widget&operator=(Widge rhs)
{
    swap(*this,rhs);
    return *this;
}
```

