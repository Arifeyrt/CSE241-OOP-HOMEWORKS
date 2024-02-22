# Derleme ayarları
JAVAC = javac
SRC_DIR = src
BUILD_DIR = build

# Derlenmesi gereken dosyalar
SOURCE_FILES = $(wildcard $(SRC_DIR)/*.java)
CLASS_FILES = $(patsubst $(SRC_DIR)/%.java, $(BUILD_DIR)/%.class, $(SOURCE_FILES))

# Hedef: Tüm sınıfları derle
all: $(CLASS_FILES)

# Sınıf dosyalarının derlenmesi
$(BUILD_DIR)/%.class: $(SRC_DIR)/%.java
	@mkdir -p $(@D)
	$(JAVAC) -d $(BUILD_DIR) $<

# Temizleme işlemi: Derleme çıktılarını temizle
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
