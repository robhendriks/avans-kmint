#ifndef rabbit_h
#define rabbit_h

#include "force_driven_entity.h"
#include "texture_manager.h"
#include "timer.h"

namespace okunoshima
{    
    class rabbit : public force_driven_entity
    {
        int m_id;
    public:
        rabbit(world* w, int i, const gene_map& genes) : force_driven_entity{"rabbit", w, genes, 1.0, 2.0, 0.2}, m_id{i} {}
        
        void update() override;
        void draw(graphics& g) override;
        
        int get_id() const { return m_id; }
        
        node* get_current_node() override;
    };
}

#endif

