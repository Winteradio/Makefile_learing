# 컴파일러 설정
CXX = g++

# 컴파일러 옵션
CXXFLAGS = -Wall

# 라이브러리
LDFLAGS = -L'C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x64' -ld3d9 -ld3dx9 -ldxguid

# 생성하고자 하는 실행 파일 이름
TARGET = example.exe

# 디렉토리 설정
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
HED_DIR = include/
DIX_HED_DIR = 'C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\'

# 디렉토리 안의 "경로/이름.조건형식자"들을 추출
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.cpp=.o))
DEPS = $(OBJS:.o=.d)

# $(BIN_DIR)/$(TARGET)을 만들기 위한 전부 빌드해야 한다.
all : $(BIN_DIR)/$(TARGET)

# Header & CPP files들을 활용하고
# 종속성을 확인하여 Dependency를 생성한다.
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(info STEP : Complie Source files for Object file)
	$(info $< Compling... )
	$(CXX) $(CXXFLAGS) -I$(HED_DIR) -I$(DIX_HED_DIR) -c $< -o $@ -MD $(LDFLAGS)
	$(info $< Complied... )

# Object files들을 사용하여 Linking을 한 후, Target file 생성
$(BIN_DIR)/$(TARGET) : $(OBJS)
	$(info Step : Link Object files to Targer file)
	$(info -----   [$(TARGET)]   -----)
	$(info ----- Start Linking...-----)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
	$(info -----     Linked...   -----)

.PHONY : name
name :
	echo SRCS is $(SRCS)
	echo OBJS is $(OBJS)
	echo DEPS is $(DEPS)

-include $(DEPS)
$(info Step : Include Dependency files)
