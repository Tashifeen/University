class Derived : protected Base {
public:
    // Public getter/setter for numPublic (inherited as protected)
    int getNumPublic() {
        return numPublic;
    }
    void setNumPublic(int num) {
        numPublic = num;
    }

    // Public getter/setter for numProtected (inherited as protected)
    int getNumProtected() {
        return numProtected;
    }
    void setNumProtected(int num) {
        numProtected = num;
    }

    // Public getter/setter for numPrivate (access via Base's protected methods)
    int getNumPrivate() {
        return readNumPrivate();
    }
    void setNumPrivate(int num) {
        writeNumPrivate(num);
    }
};
