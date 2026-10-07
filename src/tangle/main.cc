#include <nbt/nbt.hh>

#include <print>

int tabs = 0;

std::string tab() {
    std::string a = "";
    for(int i = 0; i < tabs; i++) {
        a += "  ";
    }
    return a;
}

std::string get_string(tangle::nbt::tag_type tag, std::shared_ptr<tangle::nbt::nbt_payload> load) {
    switch(tag) {
    case tangle::nbt::tag_type::nbt_byte:{
        auto t = ((tangle::nbt::nbt_numeric<uint8_t>*) load.get())->get_value();
        return std::format("{}", t);}
    case tangle::nbt::tag_type::nbt_short:{
        auto t = ((tangle::nbt::nbt_numeric<uint16_t>*) load.get())->get_value();
        return std::format("{}", t);}
    case tangle::nbt::tag_type::nbt_int:{
        auto t = ((tangle::nbt::nbt_numeric<uint32_t>*) load.get())->get_value();
        return std::format("{}", t);}
    case tangle::nbt::tag_type::nbt_long:{
        auto t = ((tangle::nbt::nbt_numeric<uint64_t>*) load.get())->get_value();
        return std::format("{}", t);}
    case tangle::nbt::tag_type::nbt_float:{
        auto t = ((tangle::nbt::nbt_numeric<float>*) load.get())->get_value();
        return std::format("{}", t);}
    case tangle::nbt::tag_type::nbt_double:{
        auto t = ((tangle::nbt::nbt_numeric<double>*) load.get())->get_value();
        return std::format("{}", t);}
    case tangle::nbt::tag_type::nbt_string:{
        auto t = ((tangle::nbt::nbt_string*) load.get())->string();
        return std::format("{}", t);}
    default: 
        break;
    }
    return "";
}

void print_node(tangle::nbt::nbt_tag tag);

void print_list(std::string name, tangle::nbt::nbt_list* a) {
        std::println("{}\"{}\"[{:02x}] <{} elements>", tab(), name, (uint8_t)tangle::nbt::tag_type::nbt_list, a->contents().size());
        tabs += 2;
        std::size_t i = 0;
        for(auto& ref : a->contents()) {
            std::string st = get_string(a->get_type(), ref);
            if(a->get_type() == tangle::nbt::tag_type::nbt_compound) {
                auto a  = (tangle::nbt::nbt_compound*) ref.get();
                std::println("{}\"{:02}\"[{:02x}] <{} elements>", tab(), i, (uint8_t)tangle::nbt::tag_type::nbt_compound, a->fields().size());
                tabs += 2;
                for(auto& ref : a->fields()) {
                    print_node(ref);
                }
                tabs -= 2;
            } else if (a->get_type() == tangle::nbt::tag_type::nbt_list) {
                tabs += 2;
                auto b  = (tangle::nbt::nbt_list*) ref.get();
                print_list("nested_list", b);
                tabs -= 2;
            } else {
                std::println("{}\"{:02}\"[{:02x}] = {}", tab(), i, (uint8_t)a->get_type(), st);
            }
            i++;
        }
        tabs -= 2; 
}

void print_node(tangle::nbt::nbt_tag tag) {
    if(tag.get_type() == tangle::nbt::tag_type::nbt_end) return;
    if(tag.get_type() == tangle::nbt::tag_type::nbt_compound) {
        auto a  = (tangle::nbt::nbt_compound*) tag.payload().get();
        std::println("{}\"{}\"[{:02x}] <{} elements>", tab(), tag.name(), (uint8_t)tag.get_type(), a->fields().size());
        tabs += 2;
        for(auto& ref : a->fields()) {
            print_node(ref);
        }
        tabs -= 2;
    } else if (tag.get_type() == tangle::nbt::tag_type::nbt_list) {
        auto a  = (tangle::nbt::nbt_list*) tag.payload().get();
        print_list(tag.name(), a);
    } else {
        std::string s = get_string(tag.get_type(), tag.payload());
        std::println("{}\"{}\"[{:x}] = {}", tab(), tag.name(), (uint8_t)tag.get_type(), s);
    }

}

int main() {
    std::ifstream f("Scurax.dat");
    tangle::nbt::nbt_reader t(std::move(f));
    auto a = t.get_tree();
    print_node(a);
    tangle::nbt::nbt_writer w(std::ofstream("scucopia.dat"));
    w.write(a);
    w.close();
}