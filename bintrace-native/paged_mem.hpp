#include <unordered_map>
#include <vector>
#include <utility>
#include <stdint.h>


class Page
{
public:
  Page();
  Page(uint64_t base_addr, uint32_t page_size);
  Page(const Page & page);
  bool contains(uint64_t off) const;
  uint8_t operator [](uint64_t off) const;
  uint8_t & operator [](uint64_t off);
  std::vector<uint64_t> offsets() const;
  std::vector<std::pair<uint64_t, uint64_t>> get_contiguous_ranges() const;

private:
  void setbit(uint64_t off);
  bool is_bit_set(uint64_t off) const;

private:
  uint64_t m_base_addr;
  uint32_t m_page_size;
  std::vector<uint8_t> m_bitmap;
  std::vector<uint8_t> m_content;
};


class PagedMemory
{
public:
  PagedMemory();
  PagedMemory(uint32_t page_size);
  PagedMemory(const PagedMemory &mem);
  uint8_t operator [](uint64_t addr) const;
  uint8_t at(uint64_t addr) const;
  uint8_t & operator [](uint64_t addr);
  bool contains(uint64_t addr) const;
  uint64_t get_page_size() const {return m_page_size; };
  uint64_t get_page_id(uint64_t addr) const { return addr / m_page_size; };
  uint64_t get_page_offset(uint64_t addr) const { return addr % m_page_size; };
  std::vector<uint64_t> sorted_addresses() const;
  std::vector<std::pair<uint64_t, uint64_t>> get_contiguous_ranges() const;

private:
  uint32_t m_page_size;
  std::unordered_map<uint64_t, Page> m_pages;
};

