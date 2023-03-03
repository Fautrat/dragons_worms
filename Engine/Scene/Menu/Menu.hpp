#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>


enum EElementType {
    Button = 1,
    Text,
    Zone,
};

enum EStateMenu {
    Active = 1,
    Inactive,
    Hidden,
    ToDelete,
};

struct UiElement {
    EElementType Type;
    std::string Name;
    std::function<void(void)> Callback;

    UiElement() = default;
    UiElement(EElementType type, std::string name, std::function<void(void)> callback): Type(type), Name(name), Callback(callback){};

    ~UiElement(){
        Callback = nullptr;
    }
};

class Menu {
public:
    explicit Menu(std::string name);
    virtual ~Menu(){
        GetElements().clear();
    };

    void AddButton(std::string buttonName, std::function<void(void)> callback);

//    void AddButton(std::vector<std::string> buttonNames);

    void RemoveButton(std::string buttonName);

    void AddZone(std::string shapeName, std::function<void(void)> callback);
    void RemoveZone(std::string shapeName);

    [[nodiscard]] std::string const GetName() const;

    [[nodiscard]] std::vector<std::string> GetButtons() const;

    [[nodiscard]] std::vector<std::unique_ptr<UiElement>>& GetElements();

    void SetState(EStateMenu state);
    [[nodiscard]] EStateMenu GetState() const;



private:
//    std::vector<std::string> _Buttons;
    std::vector<std::unique_ptr<UiElement>> _Elements;
    std::string _Name;
    EStateMenu _State;
};

