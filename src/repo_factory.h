class InitFactory {
    public:
        static getCoatRepo(const std::string& type) const;
        static getCartRepo(const std::string& type) const;

        static getServiceMode(const std::string& mode) const;
}
