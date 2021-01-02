#include <vector>

template<class T, size_t BLOCKS_SIZE>
class allocator {
private:
    T* buffer;
    std::vector<T*> free_blocks;

public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = size_t;

    allocator() noexcept {
        buffer = nullptr;
    }

    ~allocator() {
        free(buffer);
    }

    template<class U> //type conversation
    struct rebind {
        using other = allocator<U, BLOCKS_SIZE>;
    };

    pointer allocate(){
        if (!buffer) {
            buffer = (pointer)malloc(BLOCKS_SIZE * sizeof(T));
            for (int i = 0; i < BLOCKS_SIZE; ++i) {
                free_blocks.push_back(buffer + i);
            }
        }

        if (free_blocks.empty()) {
            throw std::bad_alloc();
        }

        pointer p = free_blocks[free_blocks.size() - 1];
        free_blocks.pop_back();
        return p;

    }

    void deallocate(pointer p) {
        free_blocks.push_back(p);
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }
};

