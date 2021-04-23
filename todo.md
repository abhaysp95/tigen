* give thought to use move constructor or not
* if move constructor used then whether it'll be explicit or not
* whether to use explicit copy constructor or not(using non-explicit copy constructor currently)
* Think about whether to use(or whether it could be used) initializer_list or not
* see the places where you can return const entities as return(like entities::room& function())
* should I be returning the instance of `data` class as value(on stack) or as reference(on heap) ?
* search if having `explicit` constraint with _paramterized_ constructor makes sense, if you class also have a _parentless_ constructor
* see if the upper level entities of `schedule` are calling the _writable get_sec_classes()_(which is supposed to update a flag), I have two signatures with same name, and suppose, compiler can implicitly get what it wants
* also try the explicit way for to tell compiler which type of container in return you want from _get_sec_classes()_(const or non-const, non-const one's function will be the one which is updating flag)
* see wherever you're returning the instance of class(something like singleton class), if you can make that reference const
* an idea is that everytime, _tournament_population_, _mutate_population_, _crossover_population_ and _crossover_schedule_ is generated dynamically, I should check and free the previous of it and then create a new one.
