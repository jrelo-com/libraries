template<typename Generic>
LList<Generic>::LList() {
	removeAll();
}

template<typename Generic>
LList<Generic>::~LList() {
	removeAll();
}

template<typename Generic>
void LList<Generic>::add(Generic *generic) {
    Node<Generic> *node = new Node<Generic>();
    if (_size == 0 ) {
        node->previous = NULL;
    } else {
        node->previous = last;
    }

    node->generic = generic;
    last = node;
    _size++;
}

template<typename Generic>
Generic* LList<Generic>::get(int index) {
    int count = _size - index - 1;
    Node<Generic> *temp = last;

    for (int i = 0; i < count; i++) {
        temp = temp->previous;
    }
    return temp->generic;
}

template<typename Generic>
int LList<Generic>::size() {
    return _size;
}

template<typename Generic>
void LList<Generic>::removeAll() {
    if (_size == 0) {
        return;
    }

    Node<Generic> *temp = last;
    Node<Generic> *temp1 = NULL;
    int temp3 = _size;
    for (int i = 0; i < temp3; i++) {
        temp1 = temp;
        temp = temp->previous;
        delete  temp1;
        --_size;
    }
}



