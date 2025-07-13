classDiagram
    class HardwareComponent {
        - int id
        - QString name
        - QString type
        - QString manufacturer
        - QString model
        - double price
        - QString specifications
        + HardwareComponent(...)
        + getId() int
        + getName() QString
        + getType() QString
        + getManufacturer() QString
        + getModel() QString
        + getPrice() double
        + getSpecifications() QString
        + setName(QString)
        + setType(QString)
        + setManufacturer(QString)
        + setModel(QString)
        + setPrice(double)
        + setSpecifications(QString)
    }

    class Repository {
        <<interface>>
        + add(HardwareComponent)
        + remove(HardwareComponent)
        + update(HardwareComponent, HardwareComponent)
        + getAll() vector<HardwareComponent>
        + save()
        + load()
        + clear()
    }
    class JSONRepository {
        - QString filename
        - vector<HardwareComponent> components
        + JSONRepository(QString)
        + add(HardwareComponent)
        + remove(HardwareComponent)
        + update(HardwareComponent, HardwareComponent)
        + getAll() vector<HardwareComponent>
        + save()
        + load()
        + clear()
    }
    class CSVRepository {
        - QString filename
        - vector<HardwareComponent> components
        + CSVRepository(QString)
        + add(HardwareComponent)
        + remove(HardwareComponent)
        + update(HardwareComponent, HardwareComponent)
        + getAll() vector<HardwareComponent>
        + save()
        + load()
        + clear()
    }
    Repository <|-- JSONRepository
    Repository <|-- CSVRepository

    class Command {
        <<interface>>
        + execute()
        + undo()
    }
    class AddCommand {
        - Repository& repository
        - HardwareComponent component
        + AddCommand(Repository&, HardwareComponent)
        + execute()
        + undo()
    }
    class RemoveCommand {
        - Repository& repository
        - HardwareComponent component
        + RemoveCommand(Repository&, HardwareComponent)
        + execute()
        + undo()
    }
    class UpdateCommand {
        - Repository& repository
        - HardwareComponent oldComponent
        - HardwareComponent newComponent
        + UpdateCommand(Repository&, HardwareComponent, HardwareComponent)
        + execute()
        + undo()
    }
    Command <|-- AddCommand
    Command <|-- RemoveCommand
    Command <|-- UpdateCommand

    class IFilter {
        <<interface>>
        + matches(HardwareComponent) bool
    }
    class TypeFilter {
        - QString type
        + TypeFilter(QString)
        + matches(HardwareComponent) bool
    }
    class ManufacturerFilter {
        - QString manufacturer
        + ManufacturerFilter(QString)
        + matches(HardwareComponent) bool
    }
    class PriceRangeFilter {
        - double minPrice
        - double maxPrice
        + PriceRangeFilter(double, double)
        + matches(HardwareComponent) bool
    }
    class AndFilter {
        - vector<shared_ptr<IFilter>> filters
        + addFilter(shared_ptr<IFilter>)
        + matches(HardwareComponent) bool
    }
    class OrFilter {
        - vector<shared_ptr<IFilter>> filters
        + addFilter(shared_ptr<IFilter>)
        + matches(HardwareComponent) bool
    }
    IFilter <|-- TypeFilter
    IFilter <|-- ManufacturerFilter
    IFilter <|-- PriceRangeFilter
    IFilter <|-- AndFilter
    IFilter <|-- OrFilter

    class Controller {
        - Repository& repository
        - stack<unique_ptr<Command>> undoStack
        - stack<unique_ptr<Command>> redoStack
        - shared_ptr<IFilter> currentFilter
        + Controller(Repository&)
        + addComponent(HardwareComponent)
        + removeComponent(HardwareComponent)
        + updateComponent(HardwareComponent, HardwareComponent)
        + canUndo() bool
        + canRedo() bool
        + undo()
        + redo()
        + setFilter(shared_ptr<IFilter>)
        + clearFilter()
        + getAllComponents() vector<HardwareComponent>
        + getFilteredComponents() vector<HardwareComponent>
        + createTypeFilter(QString) shared_ptr<IFilter>
        + createManufacturerFilter(QString) shared_ptr<IFilter>
        + createPriceRangeFilter(double, double) shared_ptr<IFilter>
        + createAndFilter() shared_ptr<AndFilter>
        + createOrFilter() shared_ptr<OrFilter>
    }

    class MainWindow {
        - static int nextId
        - int currentComponentId
        - Controller& controller
        - QTableWidget* tableWidget
        - QPushButton* addButton
        - QPushButton* removeButton
        - QPushButton* updateButton
        - QPushButton* undoButton
        - QPushButton* redoButton
        - QLineEdit* nameEdit
        - QComboBox* typeCombo
        - QLineEdit* manufacturerEdit
        - QLineEdit* modelEdit
        - QDoubleSpinBox* priceSpinBox
        - QTextEdit* specificationsEdit
        - QGroupBox* filterGroup
        - QComboBox* filterTypeCombo
        - QLineEdit* filterManufacturerEdit
        - QDoubleSpinBox* filterMinPriceSpinBox
        - QDoubleSpinBox* filterMaxPriceSpinBox
        - QRadioButton* useOrFilterRadio
        - QRadioButton* useAndFilterRadio
        - QButtonGroup* filterButtonGroup
        - QPushButton* applyFilterButton
        - QPushButton* clearFilterButton
        + MainWindow(Controller&, QWidget*)
    }
    MainWindow --> Controller
    Controller --> Repository
    Controller --> Command
    Controller --> IFilter
    AddCommand --> Repository
    RemoveCommand --> Repository
    UpdateCommand --> Repository
    AddCommand --> HardwareComponent
    RemoveCommand --> HardwareComponent
    UpdateCommand --> HardwareComponent
    JSONRepository --> HardwareComponent
    CSVRepository --> HardwareComponent
    TypeFilter --> HardwareComponent
    ManufacturerFilter --> HardwareComponent
    PriceRangeFilter --> HardwareComponent
    AndFilter --> IFilter
    OrFilter --> IFilter